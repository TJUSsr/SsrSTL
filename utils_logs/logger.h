//
// Created by Administrator on 2018/5/10.
//


#ifndef SSRSTL_LOGGER_H
#define SSRSTL_LOGGER_H

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#include "../ssrstl_lib/spdlog/spdlog.h"

namespace SSRSTL{

    extern std::shared_ptr<spdlog::logger> my_logger;
    extern std::shared_ptr<spdlog::logger> console;
    void init();
}
#endif //SSRSTL_LOGGER_H
