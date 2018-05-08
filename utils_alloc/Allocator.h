//
// Created by Administrator on 2018/5/8.
//

#ifndef SSRSTL_ALLOCATOR_H
#define SSRSTL_ALLOCATOR_H

#include "alloc.h"
#include "Construct.h"
#include <cassert>
#include <new>

namespace SSRSTL{
    /*
     * 空间配置器,基于class alloc以及construct()函数来实现空间配置
     * class alloc负责申请内存,construct()函数在申请内存的基础上构建对象
    */
    template <typename T>
    class Allocator{
    public:
        /*
         * 之所以没有
         * typedef const T          const_value_type;
         * 是因为这属于顶层const,参数值传递时会被忽略
         * 而const T*以及const T&属于底层const,参数值传递时并不会被忽略
        */
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef const T*            const_pointer;
        typedef T&                  reference;
        typedef const T&            const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;

        static pointer allocate();
        static pointer allocate(size_type n);
        static void deallocate(pointer ptr);
        static void deallocate(pointer ptr, size_type n);

        static void construct(pointer ptr);
        static void construct(pointer ptr,const_reference value);
        static void destroy(pointer ptr);
        static void destroy(pointer first,pointer last);
    };

    template <typename T>
    Allocator::pointer Allocator<T>::allocate() {
        //调用class alloc中的allocate分配内存
        return static_cast<pointer>(alloc::allocate(sizeof(value_type)));
    }

    template <typename T>
    Allocator::pointer Allocator<T>::allocate(size_type n) {
        //调用class alloc中的allocate分配内存
        if(n==0) return nullptr;
        return static_cast<pointer >(alloc::allocate(n* sizeof(value_type)));
    }

    template <typename T>
    void Allocator<T>::deallocate(pointer ptr) {
        //调用class alloc中的deallocate释放内存
        alloc::deallocate(ptr,sizeof(value_type));
    }

    template <typename T>
    void Allocator<T>::deallocate(pointer ptr, size_type n) {
        if(n==0) return;
        alloc::deallocate(ptr,n*sizeof(value_type));
    }

    template <typename T>
    void Allocator<T>::construct(pointer ptr) {
        new(ptr)value_type();
    }

    template <typename T>
    void Allocator<T>::construct(pointer ptr,const_reference value) {
        new(ptr)value_type(value);
    }

    template <typename T>
    void Allocator<T>::destroy(pointer ptr){
        ptr->~value_type();
    }

    template<typename T>
    void Allocator<T>::destroy(pointer first, pointer last) {
        for(;first!=last;++first){
            first->~value_type();
        }
    }
}

#endif //SSRSTL_ALLOCATOR_H
