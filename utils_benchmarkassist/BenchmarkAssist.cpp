//
// Created by Monster on 2018/5/28.
//
#include "BenchmarkAssist.h"
namespace SSRSTL{
    namespace Benchmark{
        BmAssist::TimePoint BmAssist::StartTime;
        BmAssist::TimePoint BmAssist::EndTime;
        BmAssist::DurationTime BmAssist::duringTime;

        void BmAssist::start() {
            StartTime=SteadyClock::now();
        }

        void BmAssist::finish() {
            EndTime=SteadyClock::now();
            duringTime=std::chrono::duration_cast<DurationTime>(EndTime-StartTime);
        }

        void BmAssist::dumpDuringTime(){
            SPDLOG_TRACE(console,"total {} milliseconds, {} seconds", BmAssist::millissecond(), BmAssist::second());
        }

        double BmAssist::second() {
            return duringTime.count();
        }

        double BmAssist::millissecond() {
            return second()*1000;
        }

        size_t BmAssist::memory(MemoryUnit mu) {
            long long memory=0;
#ifdef WIN32
            PROCESS_MEMORY_COUNTERS pmc;
			HANDLE hProcess = GetCurrentProcess();
			if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
				throw std::runtime_error("GetProcessMemoryInfo failed");
			CloseHandle(hProcess);
			memory=pmc.WorkingSetSize;
#else
			//经过测试，该方法只能查询当前进程所占用过的最大内存，无法查询实时内存，令人苦恼。
			//TODO 内存查询方法需要进一步确定，现在的方法有一定不足，且行且修改
			struct rusage usage;
            if(getrusage(RUSAGE_SELF,&usage)==-1)
                throw std::runtime_error("getrusage failed");
            memory = usage.ru_maxrss*4;
#endif
            switch (mu){
                case MemoryUnit::KB_:
                    memory=memory KB;
                    break;
                case MemoryUnit::MB_:
                    memory=memory MB;
                    break;
                default:
                    memory=memory GB;
            }
            return memory;
        }

    }
}
