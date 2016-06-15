#ifndef __CEPH_PMDA_H__
#define __CEPH_PMDA_H__

#include <pcp-cpp/instance_domain.hpp>
#include <pcp-cpp/pmda.hpp>

/**
 * @brief Ceph PMDA
 */

class CephPmda: public pcp::pmda {

public:
    CephPmda();


    virtual std::string get_pmda_name() const;

    virtual int get_default_pmda_domain_number() const;

    virtual std::string get_pmda_version() const;

protected:

}

#endif
