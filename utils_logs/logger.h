//
// Created by Administrator on 2018/5/10.
//
#include "../ssrstl_lib/spdlog/spdlog.h"
#include <iostream>
#ifndef SSRSTL_LOGGER_H
#define SSRSTL_LOGGER_H


namespace SSRSTL{
    //利用单例模式生成一个my_logger用于调试
    class my_logger{
    public:
        static std::shared_ptr<spdlog::logger> instance();
        //my_logger的一些初始化，设置输出格式，输出级别等等
        static void init();
        ~my_logger();
    private:
        my_logger(const my_logger&)= default;
        my_logger()= default;
        static std::shared_ptr<spdlog::logger> _instance;
    };
}
#endif //SSRSTL_LOGGER_H
