#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#include <iostream>
#include "utils_alloc&module/Algorithm.h"
#include "utils_logs/logger.h"
#include <memory>
#include <vector>

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
    init();
    std::true_type;
    is_integral<int>::value_type();
    vector<int> vec1={1,2,3,4,5,6};
    cout<<vec1.capacity()<<endl;
    vec1.resize(vec1.capacity()+7);
    cout<<vec1.capacity()<<endl;
    return 0;
}
