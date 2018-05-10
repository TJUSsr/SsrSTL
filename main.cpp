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

int main() {
    std::cout << "Hello, World!" <<__FUNCTION__<<_LOCALE_CLASSES_H<<_LOCALE_CLASSES_TCC<<std::endl;

    init();
    console->info("i am console");
    SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
    SPDLOG_DEBUG(console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);
    my_logger->debug("line #{} of function #{} in file #{}",__LINE__,__FUNCTION__,__FILE__);
    my_logger->info("function #{} in file #{}",__FUNCTION__,__FILE__);
    my_logger->error("This an error message with custom format (and custom color range between the '%^' and '%$')");
    return 0;
}
