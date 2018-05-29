// All files UTF-8

#include <iostream>
#include <memory>

#include "utils_logs/logger.h"
#include "utils_test/VectorTest.h"
#include "utils_benchmarkassist/BenchmarkAssist.h"

using namespace std;
using namespace SSRSTL;


int main() {
    init();
    VectorTest::testAllCases();
    //在os x下，为了对比不同容器运行时所占用的最大内存，只能按照如下的方式进行benchmark测试（main函数中只能又一个benchmarktest函数）
    /*
int main(){
    VectorTest::benchmarkteststdvector();
    return 0;
}
     */
    //VectorTest::benchmarkteststdvector();
    //VectorTest::benchmarktestvectorssr();
    return 0;
}
