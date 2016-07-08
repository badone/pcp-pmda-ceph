#include <boost/filesystem.hpp>

#include "cephpmda.h"

CephPmda::CephPmda()
{

}

std::string CephPmda::get_pmda_name() const
{
    return "ceph";
}

int CephPmda::get_default_pmda_domain_number() const
{
    return 136;
}

std::string CephPmda::get_pmda_version() const
{
    return "0.0.1";
}

pcp::metrics_description CephPmda::get_supported_metrics()
{
    pcp::metrics_description pmd;
    return pmd;
}

pcp::pmda::fetch_value_result CephPmda::fetch_value(const metric_id& metric )
{
    return pcp::atom(metric.type,0);
}

boost::program_options::options_description CephPmda::get_supported_options() const
{
    using namespace boost::program_options;
    options_description connectionOptions("Ceph connection options");
    // Change to show "--socket-dir dir" instead of current "--socket-dir arg"
    connectionOptions.add_options()
        ("socket-dir", value<std::string>()->default_value("/var/run/ceph/")
         PCP_CPP_BOOST_PO_VALUE_NAME("dir"),"Ceph admin socket directory");
    return connectionOptions.add(pcp::pmda::get_supported_options());
}

boost::program_options::options_description CephPmda::get_supported_hidden_options() const
{
    using namespace boost::program_options;
    options_description options;
    options.add_options()
        ("no-pmda", bool_switch(), "run as a non-PMDA for development");
    return options;
}

bool CephPmda::parse_command_line(const int argc, const char* const argv[],
                                  pmdaInterface& interface,
                                  boost::program_options::variables_map& options)
{
   // Let the parent implementation do the actual command line parsing.
    if (!pcp::pmda::parse_command_line(argc, argv, interface, options)) {
        return false; 
    }
    socket_dir = options["socket-dir"].as<std::string>();

    non_pmda_mode = ((options.count("no-pmda") > 0) && (options["no-pmda"].as<bool>()));
    return true;
}

void CephPmda::initialize_pmda(pmdaInterface& interface)
{
    using namespace boost::filesystem;
    path p(socket_dir);
    if(exists(p) && is_directory(p)) {
        for(auto dir_iter : directory_iterator(p)) {
            if(dir_iter.status().type() == socket_file && dir_iter.path().extension() == ".asok") {
                metric_sources.push_back(std::unique_ptr<CephMetricSource>(
                                         new CephMetricSource(dir_iter.path().stem().string(),
                                                              dir_iter.path().string())));
            }
        }
    }

    for(auto& source : metric_sources) {
        std::string result;
        source->ping();
        cout << source->is_enabled() << '\n';
        source->get_raw_metrics(result);
        cout << result << '\n';
    }

    // If testing in non-PMDA mode, just wait for input then throw.
    if (non_pmda_mode) {
        std::cout << "Running in non-PMDA mode; outputting to: "
                  << interface.version.two.ext->e_logfile << std::endl
                  << "Press Enter to stop." << std::endl;
        pmdaOpenLog(&interface);
        std::getchar();
        std::cout << "Stopping..." << std::endl;
        throw pcp::exception(PM_ERR_FAULT);
    }

    // Let the parent implementation initialize the rest of the PMDA.
    pcp::pmda::initialize_pmda(interface);
}


