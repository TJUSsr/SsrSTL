

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
        cout<<i<<"  "<<vec1.size()<<"  "<<vec1.capacity()<<endl;
    }
    auto ememory=Benchmark::BmAssist::memory();
    SPDLOG_TRACE(console,"{} KB memory at start, cost {} KB memory ",ememory,ememory-smemory);
    Benchmark::BmAssist::finish();
    Benchmark::BmAssist::dumpDuringTime();
};



int main() {
    union obj{
        obj* free_list_link;
        char client_data[1];
    };
    char mem[100] = { 0 };
    char mem1[100] = { 0 };

    //现在是每一块内存的开始均是一个union node结构
    //----------------------------------
    //| union obj | ....................
    // ----------------------------------
    union obj *p1 = (union obj *)mem; //用一个变量表示这个结构

    //p1->free_list_link 设置为下一个内存的起始段
    p1->free_list_link = (union obj *)mem1 ;

    //可以看到mem和client_data 两个指针值是一致的
    cout <<"mem                        = " << (void *)mem << endl;
    cout <<"p1                         = " << p1 << endl;
    cout <<"(void*)p1                  = " << (void *)p1 << endl;
    cout <<"p1->client_data            = " << (void *)p1->client_data << endl;
    cout <<"&p1->free_list_link        = " << &(p1->free_list_link) << endl;

    cout<<endl;

    cout <<"p1->free_list_link         = " << p1->free_list_link << endl;
    cout <<"(void *)p1->free_list_link = " << (void *)p1->free_list_link << endl;
    cout <<"mem1                       = " << (void *)mem1 << endl;

    return 0;
}
