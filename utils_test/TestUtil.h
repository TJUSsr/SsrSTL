//
// Created by Monster on 2018/5/27.
//

#ifndef SSRSTL_TESTUTIL_H
#define SSRSTL_TESTUTIL_H

#include "../utils_logs/logger.h"
#include <iterator>
#include <string>
#include <iostream>
namespace SSRSTL{
    namespace Test{
        template <class Container>
        void log_container(Container& container, const std::string& name=""){
            SPDLOG_TRACE(console,"Container {}",name);
            for(auto val:container){
                std::cout<<val<<" ";
            }
            std::cout<<std::endl;
        }

        template <class Con1, class Con2>
        bool container_equal(Con1& con1, Con2& con2){
            SPDLOG_TRACE(console,"To judge equal or not");
            auto first1=std::begin(con1), last1=std::end(con1);
            auto first2=std::begin(con2), last2=std::end(con2);
            for(;first1!=last1&&first2!=last2;++first1,++first2){
                if(*first1!=*first2){
                    SPDLOG_TRACE(console,"false");
                    return false;
                }
            }
            SPDLOG_TRACE(console,"true");
            return true;
        };

    }
}

#endif //SSRSTL_TESTUTIL_H
