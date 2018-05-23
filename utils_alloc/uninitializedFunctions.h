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

    //***未初始化拷贝函数，如果是POD类型的数据，直接memcpy，否则挨个复制
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
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(const InputIterator& first, const InputIterator& last, const ForwardIterator& result){
        typedef typename _type_traits<_iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
        return  _uninitialized_copy_aux(first,last,result,is_POD_type());
    };

    //****未初始化fill_n函数
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(const ForwardIterator& first, const ForwardIterator& last, const T& value, _true_type){
        //TODO
    };



}


#endif //SSRSTL_UNINITIALIZEDFUNCTIONS_H
