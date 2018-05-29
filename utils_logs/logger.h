//
// Created by Administrator on 2018/5/10.
//


#ifndef SSRSTL_LOGGER_H
#define SSRSTL_LOGGER_H
/*
 * 利用SPDLOG_TRACE以及SPDLOG_DEBUG宏定义可以实现运行时Compile time log levels
 */
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#include "../ssrstl_lib/spdlog/spdlog.h"

namespace SSRSTL{

    extern std::shared_ptr<spdlog::logger> my_logger;
    extern std::shared_ptr<spdlog::logger> console;
    void init();
}
#endif //SSRSTL_LOGGER_H
