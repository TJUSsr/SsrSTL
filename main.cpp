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
    vector<int> vec1={1};
    vector<int> vec2={1,2};
    show(is_integral<int* >::type());
    show(is_integral<size_t >::type());
    auto ret= SSRSTL::find_first_of(vec1.begin(),vec1.end(),vec2.begin(),vec2.end());
    if(ret==vec1.begin()){
        SPDLOG_TRACE(console,"true");
        cout<<"true"<<endl;
    }
    else {
        SPDLOG_TRACE(console, "false");
        cout<<"false"<<endl;
    }
    return 0;
}
