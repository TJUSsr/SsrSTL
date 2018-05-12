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

int main() {
    const int& i=1;
    cout<<i<<endl;
    return 0;
}
