//
// Created by Monster on 2018/5/22.
//

#ifndef SSRSTL_VECTOR_SSR_IMPL_H
#define SSRSTL_VECTOR_SSR_IMPL_H

#include "vector_ssr.h"

namespace SSRSTL{
    //************构造函数，复制构造函数，移动语意复制构造函数，复制运算符，移动语意复制运算符，析构函数*******
    //构造函数
    template<typename T, class Alloc>
    vector_ssr<T, Alloc>::vector_ssr(const typename vector_ssr::size_type &n) {
        allocAndFillN(n,value_type());
    }

    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const size_type &n, const value_type &value) {
        vector_aux(n,value,typename std::is_integral<size_type >::type());
    }

    template<typename T, class Alloc>
    template<class InputIterator>
    vector_ssr<T,Alloc>::vector_ssr(const InputIterator &first, const InputIterator &last) {
        vector_aux(first,last,typename std::is_integral<InputIterator>::type());
    }

    //复制构造函数
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const vector_ssr &v) {
        allocAndCopy(v.begin(),v.end());
    }

    //移动语意复制构造函数,相当于移交v对原有内存的控制权
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(vector_ssr &&v) {
        start_=v.begin();
        finish_=v.end();
        endOfStorage_=v.endOfStorage();
        v.set_to_nullptr();
    }
    //注意复制运算符返回的是引用
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>& vector_ssr<T,Alloc>::operator=(const vector_ssr &v) {
        if(this!=&v)
            allocAndCopy(v.begin(),v.end());
        return *this;
    }
    //移动语意复制运算符，注意返回的是引用
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>& vector_ssr<T,Alloc>::operator=(vector_ssr &&v) {
        if(this!=&v){
            //首先析构现有的元素释放现在的内存
            destroyAndDeallocate();
            start_=v.begin();
            finish_=v.end();
            endOfStorage_=v.endOfStorage();
            v.set_to_nullptr();
        }
        return *this;
    }
    //析构函数
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::~vector_ssr() {
        destroyAndDeallocate();
    }
    //**容量相关resize(),reserve()**********
    //resize()会构造默认值填充
    template<typename T, class Alloc>
    void vector_ssr<T,Alloc>::resize(size_type n, value_type value=value_type()) {
        //n与现有size()的大小有四种关系，但是n==size()时不进行任何操作
        if(n<size()){
            dataAlloc::destroy(start_+n,finish_);
        }else if(n>size()&&n<=capacity()){
            auto lengthOfInsert=n-size();
            //TODO
        }else{

        }
        return;
    }
};

#endif //SSRSTL_VECTOR_SSR_IMPL_H
