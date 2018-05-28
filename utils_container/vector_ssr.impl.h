//
// Created by Monster on 2018/5/22.
//

#ifndef SSRSTL_VECTOR_SSR_IMPL_H
#define SSRSTL_VECTOR_SSR_IMPL_H

namespace SSRSTL{
    //************构造函数，复制构造函数，移动语意复制构造函数，复制运算符，移动语意复制运算符，析构函数*******
    //构造函数
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const typename vector_ssr::size_type &n) {
        allocAndFillN(n,value_type());
    }

    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const size_type &n, const vector_ssr::value_type &value) {
        vector_aux(n,value,typename std::is_integral<size_type >::type());
    }

    template<typename T, class Alloc>
    template<class InputIterator>
    vector_ssr<T,Alloc>::vector_ssr( InputIterator first, InputIterator last) {
        vector_aux(first,last,typename std::is_integral<InputIterator>::type());
    }
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const std::initializer_list<T>& list) {
        vector_aux(list.begin(),list.end(),std::false_type());
    }

    //复制构造函数
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(const vector_ssr &v) {
        allocAndCopy(v.begin(),v.end());
    }

    //移动语意复制构造函数,相当于移交v对原有内存的控制权
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::vector_ssr(vector_ssr &&v) noexcept {
        start_=v.begin();
        finish_=v.end();
        endOfStorage_=v.endOfStorage();
        v.start_=v.finish_=v.endOfStorage_= nullptr;
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
            v.start_=v.finish_=v.endOfStorage_= nullptr;
        }
        return *this;
    }

    template<typename T, class Alloc>
    vector_ssr<T,Alloc>& vector_ssr<T,Alloc>::operator=(const std::initializer_list<T>& list) {
        Test::log_container(list,"initialized_list");
        if(size()>=list.size()){
            dataAlloc::destroy(start_+list.size(),finish_);
            SSRSTL::uninitialized_copy(list.begin(),list.end(),start_);
            finish_=start_+list.size();
        } else if(capacity()>=list.size()){
            SSRSTL::uninitialized_copy(list.begin(),list.end(),start_);
            finish_=start_+list.size();
        } else{
            destroyAndDeallocate();
            allocAndCopy(list.begin(),list.end());
        }
        return *this;
    }

    //析构函数
    template<typename T, class Alloc>
    vector_ssr<T,Alloc>::~vector_ssr() {
        destroyAndDeallocate();
    }
    /*
     * 重载== !=运算符, 友元函数 == !=运算符
     */
    template <typename T, class Alloc>
    bool vector_ssr<T,Alloc>::operator==(const vector_ssr<T,Alloc> &v) const {
        if(size()!=v.size())
            return false;
        else{
            auto ptr1=start_;
            auto ptr2=v.begin();
            for(;ptr1!=finish_;++ptr1,++ptr2){
                if(*ptr1!=*ptr2)
                    return false;
            }
            return true;
        }
    }
    template <typename T, class Alloc>
    bool vector_ssr<T, Alloc>::operator!=(const vector_ssr<T,Alloc>& v) const {
        return !(*this==v);
    };
    template <typename T,class Alloc>
    bool operator==(const vector_ssr<T,Alloc>&v1, const vector_ssr<T,Alloc>&v2){
        return v1.operator==(v2);
    };
    template <typename T,class Alloc>
    bool operator!=(const vector_ssr<T,Alloc>&v1, const vector_ssr<T,Alloc>&v2){
        return !(v1==(v2));
    };
    //**容量相关resize(),reserve()**********
    //resize()会构造默认值填充
    template<typename T, class Alloc>
    void vector_ssr<T,Alloc>::resize(size_type n, value_type value) {
        //n与现有size()的大小有四种关系，但是n==size()时不进行任何操作
        if(n<size()){
            dataAlloc::destroy(start_+n,finish_);
        }else if(n>size()&&n<=capacity()){
            auto lengthOfInsert=n-size();
            finish_=SSRSTL::uninitialized_fill_n(finish_,lengthOfInsert,value);
        }else{
            auto lengthOfInsert=n-size();
            iterator newstart=dataAlloc::allocate(getNewCapacity(lengthOfInsert));
            iterator newfinish=SSRSTL::uninitialized_copy(begin(),end(),newstart);
            newfinish=SSRSTL::uninitialized_fill_n(newfinish,lengthOfInsert,value);
            destroyAndDeallocate();
            start_=newstart;
            finish_=newfinish;
            endOfStorage_=start_+n;
        }
    }
    //reserve()函数，只会改变capacity，且需求的capacity比现有小时，不做任何操作
    template<typename T, class Alloc>
    void vector_ssr<T,Alloc>::reserve(size_type n) {
        if(n<=capacity())
            return;
        iterator newstart=dataAlloc::allocate(getNewCapacity(n));
        iterator newfinish=SSRSTL::uninitialized_copy(begin(),end(),newstart);
        destroyAndDeallocate();
        start_=newstart;
        finish_=newfinish;
        endOfStorage_=start_+n;
    }
    /*
     * celar(),使size()为0，capacity()不变
     * swap(),和一个vector交换
     * push_back()
     * pop_back()
     * insert(),返回插入位置的迭代器
     * erase(),返回的迭代器指向被删除元素后面的元素
     */
    template<typename T, class Alloc>
    void vector_ssr<T, Alloc>::clear() {
        dataAlloc::destroy(start_,finish_);
        finish_=start_;
    }
    template<typename T, class Alloc>
    void vector_ssr<T, Alloc>::swap(vector_ssr &v) {
        SSRSTL::swap(start_,v.start_);
        SSRSTL::swap(finish_,v.finish_);
        SSRSTL::swap(endOfStorage_,v.endOfStorage_);
    }
    template<typename T, class Alloc>
    void vector_ssr<T, Alloc>::push_back(const value_type &value) {
        insert(end(),value);
    }
    template<typename T, class Alloc>
    void vector_ssr<T, Alloc>::pop_back() {
        --finish_;
        dataAlloc::destroy(finish_);
    }
    template<typename T, class Alloc>
    typename vector_ssr<T,Alloc>::iterator vector_ssr<T, Alloc>::insert(vector_ssr::iterator position,
                                                               const value_type &value) {
        auto dis=std::distance(begin(),position);
        insert(position,1,value);
        return begin()+dis;
    }
    template<typename T, class Alloc>
    void vector_ssr<T, Alloc>::insert(vector_ssr::iterator position, const vector_ssr::size_type &n,
                                      const value_type &value) {
        insert_aux(position,n,value,typename std::is_integral<size_type>::type());
    }
    template<typename T, class Alloc>
    template<class InputIterator>
    void vector_ssr<T, Alloc>::insert(vector_ssr::iterator position, InputIterator first, InputIterator last) {
        insert_aux(position,first,last,typename std::is_integral<InputIterator>::type());
    }

    template<typename T, class Alloc>
    typename vector_ssr<T,Alloc>::iterator vector_ssr<T, Alloc>::erase(vector_ssr::iterator position) {
        return erase(position,position+1);
    }
    //first,last前闭后开，last不会被删除
    template<typename T, class Alloc>
    typename vector_ssr<T,Alloc>::iterator vector_ssr<T, Alloc>::erase(vector_ssr::iterator first, vector_ssr::iterator last) {
        auto lenOfTail=end()-last;
        auto lenOfRemoved=last-first;
        finish_=finish_-lenOfRemoved;
        for(;lenOfRemoved!=0;--lenOfRemoved){
            auto temp=last-lenOfRemoved;
            *temp=*(last++);
        }
        return first;
    }


};

#endif //SSRSTL_VECTOR_SSR_IMPL_H
