#ifndef ADD_H
#define ADD_H

#pragma once

#define PCP_CPP_SKIP_PCP_PMDA_INSTANCE_DEFINITION

#include <pcp-cpp/pmda.hpp>
#include <pcp-cpp/atom.hpp>

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

    virtual pcp::metrics_description get_supported_metrics();

    virtual pcp::pmda::fetch_value_result fetch_value(const metric_id &);

protected:

};
#endif
