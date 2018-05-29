//
// Created by Monster on 2018/5/28.
//

#ifndef SSRSTL_BENCHMARKASSIST_H
#define SSRSTL_BENCHMARKASSIST_H

#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <ratio>
#include <utility>
#include "../utils_logs/logger.h"
#ifdef WIN32
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib,"psapi.lib")
#else
#include <sys/resource.h>
#include <sys/time.h>
#endif

namespace SSRSTL{
    namespace Benchmark{
        class BmAssist{
        public:
            typedef std::chrono::steady_clock SteadyClock;
            typedef SteadyClock::time_point TimePoint;
            typedef std::chrono::duration<double,std::ratio<1,1>> DurationTime;//单位秒
            enum class MemoryUnit{KB_,MB_,GB_};
        private:
            #define KB / 1024
            #define MB KB /1024
            #define GB MB /1024

            static DurationTime duringTime;
            static TimePoint  StartTime;
            static TimePoint  EndTime;
        public:
            static void start();
            static void finish();
            static void dumpDuringTime();

            static double second();//以秒为单位返回
            static double millissecond();//以毫秒为单位返回

            static size_t memory(MemoryUnit mu=MemoryUnit::KB_);//查询当前程序内存用量
        };
    }
}



#endif //SSRSTL_BENCHMARKASSIST_H
