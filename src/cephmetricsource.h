#ifndef CEPHMETRICSOURCE_H
#define CEPHMETRICSOURCE_H

#include <string>

class CephMetricSource {

public:
    CephMetricSource() = delete;
    CephMetricSource(const std::string name, const std::string sock) : name(name), socket(sock) {}

    std::string get_name() const { return name; }
    std::string get_socket() const { return socket; }
private:
    std::string name;
    std::string socket;
};

#endif // CEPHMETRICSOURCE_H
