//
// Created by Monster on 2018/5/22.
//

#ifndef SSRSTL_UNINITIALIZEDFUNCTIONS_H
#define SSRSTL_UNINITIALIZEDFUNCTIONS_H

#include <cstring>
#include <utility>
#include "Algorithm.h"
#include "Construct.h"
#include "../utils_iterator/Iterator.h"
#include "../utils_typetraits/Typetraits.h"

namespace SSRSTL{
    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(const InputIterator& first, const InputIterator& last, const ForwardIterator& result, _true_type){
        memcpy(result,first,(last-first)* sizeof(*first));
        return result+(last-first);
    };

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(const InputIterator& first, const InputIterator& last, const ForwardIterator& result, _false_type){
        int i=0;
        for(;first!=last;++first,++i){
            construct((result+i),*first);
        }
        return result+i;
    };

}


#endif //SSRSTL_UNINITIALIZEDFUNCTIONS_H
