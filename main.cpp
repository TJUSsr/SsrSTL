

/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#include <iostream>
#include <memory>

#include "utils_logs/logger.h"
#include "utils_test/VectorTest.h"
#include "utils_benchmarkassist/BenchmarkAssist.h"

using namespace std;
using namespace SSRSTL;

void teststd(){
    vector<int> vec1;
    auto smemory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start ",smemory);
    Benchmark::BmAssist::start();
    int i=0;
    for(;i!=10000000;++i){
        vec1.push_back(i);
    }
    auto ememory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at end, cost {} KB memory",ememory, ememory-smemory);
    Benchmark::BmAssist::finish();
    Benchmark::BmAssist::dumpDuringTime();
}
void testssr(){
    vector_ssr<int> vec1;
    auto smemory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start ",smemory);
    Benchmark::BmAssist::start();
    int i=0;
    for(;i!=10000000;++i){
        vec1.push_back(i);
    }
    auto ememory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start, cost {} KB memory ",ememory,ememory-smemory);
    Benchmark::BmAssist::finish();
    Benchmark::BmAssist::dumpDuringTime();
};



int main() {
    init();
    console->trace("test spdlog {}",__FUNCTION__);
    teststd();
    testssr();
    return 0;
}
