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

pcp::pmda::fetch_value_result CephPmda::fetch_value(const metric_id & metric )
{
    return pcp::atom(metric.type,0);
}

