#ifndef CEPHMETRICSOURCE_H
#define CEPHMETRICSOURCE_H

// Boost headers that depend on boost/cstdint.hpp must be included before any
// PCP headers, because pcp/config.h sets a number of macros like ULONGLONG_MAX
// which fool Boost into thinking we're on an unknown, non-standard platform.
// In this case common/admin_socket.h includes boost headers
#include "common/admin_socket.h"
#include "common/admin_socket_client.h"

#include <pcp-cpp/pmda.hpp>
#include <pcp-cpp/atom.hpp>

class CephMetricSource {

public:
    CephMetricSource() = delete;
    CephMetricSource(const std::string name, const std::string sock) : name(name),
                     socket(sock), client(sock) {}

    std::string get_name() const { return name; }
    std::string get_socket() const { return socket; }
    std::string get_err() const { return socket; }
    bool is_enabled() const { return enabled; }
    void ping() { err = client.ping(&enabled); }
    bool get_raw_metrics(std::string& response) {
        err = client.do_request("{\"prefix\":\"perf dump\"}", &response);
        return err.empty() ? true : false;
    }

private:
    std::string name;
    std::string socket;
    bool enabled = true;
    std::string err;
    AdminSocketClient client;
};

#endif // CEPHMETRICSOURCE_H
