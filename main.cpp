#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#include <iostream>
#include "utils_logs/logger.h"
#include <memory>


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

int main() {
    show(is_integral<int* >::type());
    show(is_integral<size_t >::type());
    return 0;
}
