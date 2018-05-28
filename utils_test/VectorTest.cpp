//
// Created by Monster on 2018/5/28.
//

#include "VectorTest.h"

namespace SSRSTL{
    namespace VectorTest{
        /*
        void testAllCases(){
            testCase1();
            testCase2();
            testCase3();
            testCase4();
            testCase5();
            testCase6();
            testCase7();
            testCase7();
            testCase8();
            testCase9();
            testCase10();
            testCase11();
            testCase12();
            testCase13();
            testCase14();
            testCase15();
        }*/

        void testCase1(){
            stdvec<std::string> v1(10,"ssr");
            ssrvec<std::string> v2(10,"ssr");
            assert(SSRSTL::Test::container_equal(v1,v2));

            stdvec<std::string> v3(10);
            ssrvec<std::string> v4(10);
            assert(SSRSTL::Test::container_equal(v3,v4));

            std::array<std::string,3> arr={"abc","def","ghi"};
            stdvec<std::string> v5(arr.begin(),arr.end());
            ssrvec<std::string> v6(arr.begin(),arr.end());
            assert(SSRSTL::Test::container_equal(v5,v6));
        }

        void testCase2(){
            stdvec <int> temp1(10,0);
            ssrvec <int> temp2(10,0);

            auto v1(temp1);
            auto v2(temp2);
            assert(SSRSTL::Test::container_equal(v1,v2));

            auto v3(std::move(temp1));
            auto v4(std::move(temp2));
        }






    }
}