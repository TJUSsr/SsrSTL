//
// Created by Monster on 2018/5/29.
//
#include "string_ssr.h"

namespace SSRSTL {
    void string_ssr::moveData(string_ssr& str){
        start_=str.start_;
        finish_=str.finish_;
        endOfStorage_=str.endOfStorage_;
        str.start_=str.finish_=str.endOfStorage_=0;
    }
    
    string_ssr::size_type string_ssr::getNewCapacity(size_type len) const{
        auto oldCapacity=capacity();
        auto lengthAppend=SSRSTL::max(len,oldCapacity);
        return oldCapacity+lengthAppend;
    }
}

