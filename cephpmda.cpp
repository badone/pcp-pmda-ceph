#include "cephpmda.h"

Cephpmda::CephPmda()
{

}

std::string CephPmda::get_pmda_name() const
{
    return "ceph";
}

virtual int CephPmda::get_default_pmda_domain_number() const
{
    return 136;
}

virtual std::string CephPmda::get_pmda_version() const
{
    return "0.0.1";
}
