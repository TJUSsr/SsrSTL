//
// Created by Monster on 2018/5/28.
//

#include "VectorTest.h"

namespace SSRSTL{
    namespace VectorTest{
        void testAllCases(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
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
            benchmarkteststdvector();
            benchmarktestvectorssr();
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase1(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
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
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase2(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec <int> temp1(10,0);
            ssrvec <int> temp2(10,0);

            auto v1(temp1);
            auto v2(temp2);
            assert(SSRSTL::Test::container_equal(v1,v2));

            auto v3(std::move(temp1));
            auto v4(std::move(temp2));
            assert(SSRSTL::Test::container_equal(v3,v4));

            auto v5=v1;
            auto v6=v2;
            assert(SSRSTL::Test::container_equal(v5,v6));

            auto v7=std::move(v3);
            auto v8=std::move(v4);
            assert(SSRSTL::Test::container_equal(v7,v8));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase3(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec<int> v1,v2;
            for(int i=0;i!=100;++i){
                v1.push_back(i);
                v2.push_back(i);
            }

            assert(SSRSTL::Test::container_equal(v1,v2));
            assert(v1==v2);
            assert(!(v1!=v2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase4(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec<int> myvector;
            for(int i=1;i<=5;++i)
                myvector.push_back(i);

            auto i=1;
            for(ssrvec<int>::iterator it=myvector.begin();it!=myvector.end();++it,++i){
                assert(*it==i);
            }

            i=1;
            for(ssrvec<int>::const_iterator it=myvector.begin();it!=myvector.end();++it,++i){
                assert(*it==i);
            }
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase5(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec<int> myvector(5);
            int i=0;
            ssrvec <int>::reverse_iterator rit=myvector.rbegin();
            for(;rit!=myvector.rend();++rit)
                *rit=++i;
            i=5;
            for(ssrvec<int>::iterator it=myvector.begin();it!=myvector.end();++it,--i){
                assert(*it==i);
            }
            i=1;
            for(ssrvec<int>::reverse_iterator it=myvector.rbegin();rit!=myvector.rend();++rit,++i){
                assert(*rit==i);
            }
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase6(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec <int> v(11,0);
            assert(v.size()==11);

            v.resize(5);
            assert(v.size()==5);

            v.resize(20);
            assert(v.size()==20);
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase7(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec<int> v;
            v.reserve(20);
            assert(v.capacity()==20);
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase8(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec <int> v1(10);
            ssrvec <int> v2(10);
            for(auto i=0;i<10;++i){
                v1[i]=i;
                v2[i]=i;
            }
            assert(SSRSTL::Test::container_equal(v1,v2));

            v1.front()=99;
            v2.front()=99;
            v1.back()=100;
            v2.back()=100;
            assert(SSRSTL::Test::container_equal(v1,v2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase9(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec <int> v1(5);
            ssrvec <int> v2(5);

            auto p1=v1.data();
            auto p2=v2.data();
            *p1=10;++p1;*p1=20;p1[2]=100;
            *p2=10;++p2;*p2=20;p2[2]=100;
            assert(SSRSTL::Test::container_equal(v1,v2));
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
        }

        void testCase10(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec <int> foo(3,100);
            ssrvec <int> bar(2,200);
            stdvec <int> foo2(3,100);
            stdvec <int> bar2(2,200);

            assert(SSRSTL::Test::container_equal(foo, foo2));
            assert(SSRSTL::Test::container_equal(bar, bar2));

            foo.swap(bar);
            assert(SSRSTL::Test::container_equal(bar, foo2));
            assert(SSRSTL::Test::container_equal(foo, bar2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase11(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec <std::string> v1;
            ssrvec <std::string> v2;
            v1.push_back("hello");
            v1.push_back("world");
            v2.push_back("hello");
            v2.push_back("world");
            assert(SSRSTL::Test::container_equal(v1,v2));

            v1.pop_back();
            v2.pop_back();
            assert(SSRSTL::Test::container_equal(v1,v2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase12(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec<int> v1;
            ssrvec<int> v2;

            v1.insert(v1.begin(),0);
            v2.insert(v2.begin(),0);
            assert(SSRSTL::Test::container_equal(v1,v2));

            v1.insert(v1.end(),1);
            v2.insert(v2.end(),1);
            assert(SSRSTL::Test::container_equal(v1,v2));

            int arr[]={0,1,2,3,4,5,6,7,8,9};
            v1.insert(v1.end(),std::begin(arr),std::end(arr));
            v2.insert(v2.end(),std::begin(arr),std::end(arr));
            assert(SSRSTL::Test::container_equal(v1,v2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase13(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            stdvec <int> v1;
            ssrvec <int> v2;
            for(int i=1;i<=10;++i){
                v1.push_back(i);
                v2.push_back(i);
            }
            v1.erase((v1.begin()+5));
            v2.erase(v2.begin()+5);
            assert(SSRSTL::Test::container_equal(v1,v2));

            v1.erase(v1.begin(),v1.begin()+3);
            v2.erase(v2.begin(),v2.begin()+3);
            assert(SSRSTL::Test::container_equal(v1,v2));
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void testCase14(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            ssrvec <int> foo(3,100);
            ssrvec <int> bar(2,100);
            assert(!(foo==bar));
            assert(foo!=bar);
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        class TestItem{
        public:
            TestItem(){
                ++count;
            }
            TestItem(const TestItem& other){
                ++count;
            };
            virtual ~TestItem(){
                --count;
            }
            static int getCount(){
                return TestItem::count;
            }
        private:
            static int count;
        };
        int TestItem::count=0;

        void testCase15(){
            SPDLOG_TRACE(console,"In {} Function", __FUNCTION__);
            assert(TestItem::getCount()==0);
            {
                typedef ssrvec <TestItem> vec;
                vec t(10);
                t.push_back(TestItem());
                t.push_back(TestItem());
                t.push_back(TestItem());
                t.insert(t.begin(),t.begin(),t.begin()+1);
            }
            assert(TestItem::getCount()==0);
            SPDLOG_TRACE(console,"Out {} Function", __FUNCTION__);
        }

        void benchmarkteststdvector(){
            SPDLOG_TRACE(console,"In {}",__FUNCTION__);
            std::vector<int> vec1;
            auto smemory=Benchmark::BmAssist::memory(Benchmark::BmAssist::MemoryUnit::KB_);
            SPDLOG_TRACE(console,"{} KB memory at start ",smemory);
            Benchmark::BmAssist::start();
            int i=0;
            for(;i!=10000000;++i){
                vec1.push_back(i);
            }
            auto ememory=Benchmark::BmAssist::memory(Benchmark::BmAssist::MemoryUnit::KB_);
            SPDLOG_TRACE(console,"{} KB memory at end, cost {} KB memory, and the size of vec is {}",ememory, ememory-smemory,vec1.size());
            Benchmark::BmAssist::finish();
            Benchmark::BmAssist::dumpDuringTime();
            SPDLOG_TRACE(console,"Out {}",__FUNCTION__);
        }
        void benchmarktestvectorssr(){
            SPDLOG_TRACE(console,"In {}",__FUNCTION__);
            SSRSTL::vector_ssr<int> vec1;
            auto smemory=Benchmark::BmAssist::memory(Benchmark::BmAssist::MemoryUnit::KB_);
            SPDLOG_TRACE(console,"{} KB memory at start ",smemory);
            Benchmark::BmAssist::start();
            int i=0;
            for(;i!=10000000;++i){
                vec1.push_back(i);
            }
            auto ememory=Benchmark::BmAssist::memory(Benchmark::BmAssist::MemoryUnit::KB_);
            SPDLOG_TRACE(console,"{} KB memory at end, cost {} KB memory, and the size of vec is {}",ememory,ememory-smemory,vec1.size());
            Benchmark::BmAssist::finish();
            Benchmark::BmAssist::dumpDuringTime();
            SPDLOG_TRACE(console,"Out {}",__FUNCTION__);
        };
    }
}