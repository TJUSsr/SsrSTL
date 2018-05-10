//
// Created by Administrator on 2018/5/10.
//
#include "logger.h"

namespace SSRSTL{

    std::shared_ptr<spdlog::logger> my_logger::instance() {
        return _instance;
    }

    my_logger::~my_logger() {
        std::cout<<"my_logger destroyed"<<std::endl;
    }

    void my_logger::init() {
        /*
         *  设置输出级别
         *   typedef enum
         *   {
         *   trace = 0,
         *   debug = 1,
         *   info = 2,
         *   warn = 3,
         *   err = 4,
         *   critical = 5,
         *   off = 6
         *   } level_enum;
         */
        spdlog::set_level(spdlog::level::info);
        spdlog::set_pattern("[%^+++%$] [%H:%M:%S %z] [thread %t] %v");
    }

    // Create a file rotating logger with 5mb size max and 3 rotated files
    std::shared_ptr<spdlog::logger> my_logger::_instance=spdlog::rotating_logger_mt("my_logger", "./log.txt", 1048576 * 5, 3);;
}



