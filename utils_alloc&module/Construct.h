//
// Created by Administrator on 2018/5/8.
//

#ifndef SSRSTL_CONSTRUCT_H
#define SSRSTL_CONSTRUCT_H

#include "../utils_typetraits/Typetraits.h"
#include "../utils_iterator/Iterator.h"

namespace SSRSTL{
    template <typename T>
    inline void construct(T* ptr){
        //调用placement new完成对象的construct
        new(ptr)T();
    };

    template <typename T1,typename T2>
    inline void construct(T1* ptr,const T2& value){
        //调用placement new完成对象的construct
        new(ptr)T1(value);
    };

    template <typename T>
    inline void destroy(T* ptr){
        //调用析构函数完成对象的destroy
        ptr->~T();
    }

    //根据迭代器所指向的数据是否是POD类型来判断是否需要调用destory
    //POD类型的数据系统会自行析构,所以不做任何操作.
    template <class ForwardIt>
    inline void _destroy(ForwardIt first,ForwardIt last, _true_type){}

    template <class ForwardIt>
    inline void _destroy(ForwardIt first,ForwardIt last, _false_type){
        for(;first!=last;++first){
            destroy(&*first);
        }
    }

    template <class ForwardIt>
    inline void destroy(ForwardIt first,ForwardIt last){
        typedef typename _iterator_traits<ForwardIt>::value_type value_type;
        typedef typename _type_traits<value_type >::is_POD_type is_POD_type;
        _destroy(first,last,is_POD_type());
    }

}

#endif //SSRSTL_CONSTRUCT_H
