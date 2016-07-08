#ifndef CEPHPMDA_H
#define CEPHPMDA_H

#define PCP_CPP_SKIP_PCP_PMDA_INSTANCE_DEFINITION

#include "cephmetricsource.h"

/**
 * @brief Ceph PMDA
 */

class CephPmda: public pcp::pmda {

public:
    CephPmda();

    virtual std::string get_pmda_name() const override;

    virtual int get_default_pmda_domain_number() const override;

    virtual std::string get_pmda_version() const override;

protected:

    virtual pcp::metrics_description get_supported_metrics() override;

    virtual pcp::pmda::fetch_value_result fetch_value(const metric_id& id) override;

    virtual boost::program_options::options_description get_supported_options() const override;

    virtual boost::program_options::options_description get_supported_hidden_options() const override;

    virtual bool parse_command_line(const int argc, const char* const argv[],
                                              pmdaInterface& interface,
                                              boost::program_options::variables_map& options) override;

    virtual void initialize_pmda(pmdaInterface &interface) override;

private:
    bool non_pmda_mode = false;
    std::string socket_dir;
    std::vector<std::unique_ptr<CephMetricSource>> metric_sources;
};
#endif // CEPHPMDA_H
