//
// Created by Administrator on 2018/5/10.
//
#include "logger.h"
#define LOGTEXT "./log.txt"

namespace SSRSTL{

    void init() {
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
        size_t q_size = 4096; //queue size must be power of 2
        spdlog::set_async_mode(q_size);
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%^+++%$] [%H:%M:%S %z] %v");
    }

    std::shared_ptr<spdlog::logger> my_logger=spdlog::daily_logger_mt("my_logger", LOGTEXT);
    std::shared_ptr<spdlog::logger> console=spdlog::stdout_color_mt("console");

}



