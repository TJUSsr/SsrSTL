#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#include <iostream>
#include "utils_container/vector_ssr.h"
#include "utils_logs/logger.h"
#include <memory>
#include <vector>
#include "utils_test/TestUtil.h"

using namespace std;
using namespace SSRSTL;

void myplus(const int& i){
    cout<<i<<endl;
};

void show(std::false_type){
    cout<<"false"<<endl;
}
void show(std::true_type){
    cout<<"true"<<endl;
}

#include "utils_container/vector_ssr.h"

int main() {
    init();
    initializer_list<int> temp={1,2,3,4};
    vector<int> vec1={1,2,3,4,5};
    vec1={1,2,3,4};
    vector_ssr<int> vec3(temp);
    cout<<vec3.size()<<" "<<vec3.capacity()<<endl;
    Test::log_container(vec1,"vector");
    Test::log_container(vec3,"vector_ssr");
    return 0;
}
