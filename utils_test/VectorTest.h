//
// Created by Monster on 2018/5/27.
//

#ifndef SSRSTL_VECTORTEST_H
#define SSRSTL_VECTORTEST_H

#include <vector>
#include <string>
#include <iostream>

#include "TestUtil.h"
#include "../utils_logs/logger.h"
#include "../utils_container/vector_ssr.h"
#include "../utils_benchmarkassist/BenchmarkAssist.h"

namespace SSRSTL{
    namespace VectorTest{
        template <class T>
        using stdvec=std::vector<T>;

        template <class T>
        using ssrvec=SSRSTL::vector_ssr<T>;

        void testCase1();
        void testCase2();
        void testCase3();
        void testCase4();
        void testCase5();
        void testCase6();
        void testCase7();
        void testCase8();
        void testCase9();
        void testCase10();
        void testCase11();
        void testCase12();
        void testCase13();
        void testCase14();
        void testCase15();
        void benchmarkteststdvector();
        void benchmarktestvectorssr();

        void testAllCases();

    }
}


#endif //SSRSTL_VECTORTEST_H
