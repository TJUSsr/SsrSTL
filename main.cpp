#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#include <iostream>
#include <memory>
#include <vector>
#include "utils_container/vector_ssr.h"
#include "utils_logs/logger.h"
#include "utils_test/TestUtil.h"
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
    SPDLOG_TRACE(console,"total {} milliseconds, {} seconds",
                Benchmark::BmAssist::millissecond(), Benchmark::BmAssist::second());
}
void testssr(){
    vector_ssr<int> vec1;
    auto smemory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start ",smemory);
    Benchmark::BmAssist::start();
    int i=0;
    for(;i!=10000000;++i){
        vec1.push_back(i);
        cout<<i<<"  "<<vec1.size()<<"  "<<vec1.capacity()<<endl;
    }
    auto ememory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start, cost {} KB memory ",ememory,ememory-smemory);
    Benchmark::BmAssist::finish();
    Benchmark::BmAssist::dumpDuringTime();
};


int main() {
    init();
    teststd();
    cout<<endl;
    testssr();
    return 0;
}
