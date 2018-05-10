//
// Created by Administrator on 2018/5/10.
//
#include "../ssrstl_lib/spdlog/spdlog.h"
#include <iostream>

#ifndef SSRSTL_LOGGER_H
#define SSRSTL_LOGGER_H



namespace SSRSTL{

    extern std::shared_ptr<spdlog::logger> my_logger;
    extern std::shared_ptr<spdlog::logger> console;
    void init();
}
#endif //SSRSTL_LOGGER_H
