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

    //***未初始化copy()函数，如果是POD类型的数据，直接memcpy，否则挨个复制
    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type){
        memcpy(result,first,(last-first)* sizeof(*first));
        return result+(last-first);
    };

    template <class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type){
        int i=0;
        for(;first!=last;++first,++i){
            construct((result+i),*first);
        }
        return result+i;
    };
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
        typedef typename _type_traits<_iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
        return  _uninitialized_copy_aux(first,last,result,is_POD_type());
    };

    //****未初始化fill_n()函数
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type){
        SSRSTL::fill(first,last,value);
    };
    template <class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type){
        for(;first!=last;++first){
            SSRSTL::construct(first,value);
        }
    };
    template <class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value){
        SSRSTL::_uninitialized_fill_aux(first,last,value,typename SSRSTL::_type_traits<T>::is_POD_type());
    };
    //****未初始化fill_n()函数
    template <class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
            const T& value, SSRSTL::_true_type){
        return fill_n(first,n,value);
    };
    template <class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                              const T& value, SSRSTL::_false_type){
        int i=0;
        for(;i<n;++i){
            construct((T*)(first+i),value);
        }
        return (first+i);
    };
    template <class ForwardIterator, class Size, class T>
    ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                              const T& value){
        typedef typename SSRSTL::_type_traits<T>::is_POD_type is_POD;
        return SSRSTL::_uninitialized_fill_n_aux(first,n,value,is_POD());
    };



}


#endif //SSRSTL_UNINITIALIZEDFUNCTIONS_H
