#include <iostream>
#include "utils_logs/logger.h"
#include <memory>



using namespace std;
using namespace SSRSTL;

int main() {
    std::cout << "Hello, World!" <<__FUNCTION__<<_LOCALE_CLASSES_H<<_LOCALE_CLASSES_TCC<<std::endl;
    my_logger::init();
    auto logger=my_logger::instance();
    logger->info("line #{} of function #{} in file #{}",__LINE__,__FUNCTION__,__FILE__);
    logger->error("This an error message with custom format (and custom color range between the '%^' and '%$')");
    return 0;
}
