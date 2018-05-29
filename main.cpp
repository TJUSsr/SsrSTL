#include <iostream>
#include <memory>

#include "utils_logs/logger.h"
#include "utils_test/VectorTest.h"
#include "utils_benchmarkassist/BenchmarkAssist.h"

using namespace std;
using namespace SSRSTL;


int main() {
    init();
    VectorTest::benchmarkteststdvector();
    VectorTest::benchmarktestvectorssr();
    return 0;
}
