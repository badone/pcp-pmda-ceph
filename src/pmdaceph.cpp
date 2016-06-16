#include "cephpmda.h"

pcp::pmda * pcp::pmda::instance(NULL);

int main(int argc, char** argv) {
    const int result = pcp::pmda::run_daemon<CephPmda>(argc, argv);
    return result;
}
