//
// Created by Administrator on 2018/5/29.
//

#ifndef SSRSTL_STRING_SSR_H
#define SSRSTL_STRING_SSR_H

#include "../utils_logs/logger.h"
#include "../utils_alloc&module/Allocator.h"
#include "../utils_alloc&module/Algorithm.h"
#include "../utils_alloc&module/uninitializedFunctions.h"
#include "../utils_iterator/ReverseIterator.h"
#include "pair_ssr.h"

#include <cstring>
#include <type_traits>
#include <string>
#include <iostream>

namespace SSRSTL{
    class string_ssr{
    public:
        typedef char                                value_type;
        typedef char*                               iterator;
        typedef const char*                         const_iterator;
        typedef reverse_iterator_t<iterator >       reverse_iterator;
        typedef reverse_iterator_t<const_iterator > const_reverse_iterator;
        typedef char&                               reference;
        typedef const char&                         const_reference;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

    private:
        //私有成员只有三个迭代器
        iterator start_;
        iterator finish_;
        iterator endOfStorage_;
        typedef SSRSTL::Allocator<value_type > dataAlloc;

        //静态常量，直接在类内进行初始化
        //npos is a static member constant value with the greatest possible value for an element of type size_t.
        static const size_type  npos=-1;

        //一些私有函数
        void moveData(string_ssr& str);
        size_type getNewCapacity(size_type len) const;
        
        void allocateAndFillN(size_type n, value_type c);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);

        template <class InputIterator>
        iterator insert_aux_copy(iterator position, InputIterator first, InputIterator last);
        iterator insert_aux_filln(iterator position, size_t n, const_reference value);

        void string_ssr_aux(size_type n, value_type c, std::true_type);
        template <class InputIterator>
        void string_ssr_aux(InputIterator first, InputIterator last, std::false_type);
        
        //判断[position, position+lengthOfS)是否和it所指向的序列相同,返回开始相同的位置
        size_type find_aux(const_iterator it, size_type position, size_type lengthOfS, int cond) const;
        size_type rfind_aux(const_iterator cit, size_type position, size_type lengthOfS, int cond) const;
        
        //将两个序列按照字典序来进行比较
        int compare_aux(size_type position,size_type len, const_iterator cit, size_type subpos, size_type sublen) const;
        //判断ch是否在[first, last)中
        bool isContained(value_type ch,const_iterator first, const_iterator last) const;

        void destroyAndDeallocate();

        size_type changeVarWhenEqualNPOS(size_type var, size_type minuend, size_type minue) const;

    public:
        //无参数构造函数
        string_ssr():start_(0),finish_(0),endOfStorage_(0){};
        //有参数的构造函数
        string_ssr(const string_ssr& str, size_type position, size_type len=npos);
        string_ssr(const_iterator s);
        string_ssr(const_iterator s, size_type n);
        string_ssr(size_type n,value_type c);
        template <class InputIterator>
        string_ssr(InputIterator first, InputIterator last);

        //复制构造函数
        string_ssr(const string_ssr&str);
        //移动构造函数
        string_ssr(string_ssr&& str) noexcept;

        //重栽=运算符
        string_ssr& operator=(const string_ssr& str);
        string_ssr& operator=(string_ssr&& str);
        string_ssr& operator=(const_iterator s);
        string_ssr& operator=(value_type c);

        //析构函数
        ~string_ssr();

        //返回首迭代器，尾迭代器，首逆迭代器，尾逆迭代器
        iterator begin(){return start_;}
        const_iterator begin() const{return start_;}
        const_iterator cbegin() const{ return start_;}

        iterator end(){ return finish_;}
        const_iterator end() const { return finish_;}
        const_iterator cend() const { return finish_;}

        reverse_iterator rbegin(){ return reverse_iterator(finish_);}
        const_reverse_iterator rbegin() const{ return const_reverse_iterator(finish_);}
        const_reverse_iterator crbegin() const { return const_reverse_iterator(finish_);}

        reverse_iterator rend(){ return reverse_iterator(start_);}
        const_reverse_iterator rend() const { return const_reverse_iterator(start_);}
        const_reverse_iterator crend() const { return  const_reverse_iterator(start_);}

        /*
         * 容量相关的函数，size(),capacity(),length(),empty()均为const函数
         * */
        size_type size() const { return finish_-start_;}
        size_type length() const { return size();}
        size_type capacity() const { return endOfStorage_-start_;}
        bool empty() const { return finish_==start_;}

        /* 容量相关的resize(),reserve(),shrink_to_fit(),clear()
         * */
        void clear();
        void resize(size_type n);
        void resize(size_type n, value_type c);
        void reserve(size_type n);
        void shrink_to_fit();

        /* 取元素相关的函数
         * 重栽[]运算符，front(),back()函数
         * */
        reference operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference front(){ return *start_;}
        const_reference front() const{ return *start_;}
        reference back(){ return *finish_;}
        const_reference back() const{ return *finish_;}

        /* 插入相关的函数
         * push_back(),insert(),append(),+=运算符
         * */
        //insert返回string_ssr&或者 iterator
        string_ssr& insert(size_type position, const string_ssr& str);
        string_ssr& insert(size_type position, const string_ssr& str, size_type subpos, size_type sublen=npos);
        string_ssr& insert(size_type position, const_iterator s);
        string_ssr& insert(size_type position, const_iterator s, size_type n);
        string_ssr& insert(size_type position, size_type n, value_type c);
        iterator insert(iterator p, size_type n, value_type c);
        iterator insert(iterator p, value_type c);
        template <class InputIterator>
        iterator insert(iterator p, InputIterator first, InputIterator last);

        string_ssr& append(const string_ssr& str);
        string_ssr& append(const string_ssr& str, size_type subpos, size_type sublen=npos);
        string_ssr& append(const_iterator s);
        string_ssr& append(const_iterator s, size_type n);
        string_ssr& append(value_type c);
        string_ssr& append(size_type n, value_type c);
        template<class InputIterator>
        string_ssr& append(InputIterator first, InputIterator last);

        string_ssr& operator+=(const string_ssr& str);
        string_ssr& operator+=(const_iterator s);
        string_ssr& operator+=(value_type c);

        void push_back(char c){insert(end(),c);}

        /* 删除或者替换相关的函数
         * pop_back(),erase(),replace(),
         * */
        string_ssr& erase(size_type pos=0, size_type len=npos);
        iterator erase(iterator p);
        iterator erase(iterator first, iterator last);

        string_ssr& replace(size_type position, size_type len, const string_ssr& str);
        string_ssr& replace(iterator it1, iterator it2, const string_ssr& str);
        string_ssr& replace(size_type position, size_type len, const string_ssr& str, size_type subpos, size_type sublen=npos);
        string_ssr& replace(size_type position, size_type len, const_iterator s);
        string_ssr& replace(iterator it1, iterator it2, const_iterator s);
        string_ssr& replace(size_type position, size_type len, const_iterator s, size_type n);
        string_ssr& replace(iterator it1, iterator it2, const_iterator s, size_type n);
        string_ssr& replace(size_type position, size_type len, size_type n, char c);
        string_ssr& replace(iterator it1, iterator it2, size_type n, char c);

        template <class InputIterator>
        string_ssr& replace(iterator it1, iterator it2, InputIterator first, InputIterator last);

        /* 交换，拷贝，查找等相关的函数
         * */

        void swap(string_ssr& str){
            SSRSTL::swap(start_,str.start_);
            SSRSTL::swap(finish_,str.finish_);
            SSRSTL::swap(endOfStorage_,str.endOfStorage_);
        }

        //从[begin()+position,begin+position+len]复制到char* s
        size_type copy(char * s, size_type len, size_type position=0) const{
            auto ptr=SSRSTL::uninitialized_copy(begin()+position,begin()+position+len,s);
            return static_cast<size_type>(ptr-s);
        }

        size_type find(const string_ssr& str, size_type position=0) const;
        size_type find(const std::string& str, size_type position=0) const;
        size_type find(const_iterator s, size_type position=0) const;
        size_type find(const_iterator s, size_type position, size_type n) const;
        size_type find(value_type c, size_type position=0) const;

        size_type rfind(const string_ssr& str, size_type position=npos) const;
        size_type rfind(const std::string& str, size_type position=npos) const;
        size_type rfind(const_iterator s, size_type position =npos) const;
        size_type rfind(const_iterator s, size_type position, size_type n) const;
        size_type rfind(value_type c, size_type position=npos) const;

        size_type find_first_of(const string_ssr& str, size_type position=0) const;
        size_type find_first_of(const std::string& str, size_type position=0) const;
        size_type find_first_of(const_iterator s, size_type position=0) const;
        size_type find_first_of(const_iterator s, size_type position, size_type n) const;
        size_type find_first_of(value_type c, size_type position=0) const;

        size_type find_last_of(const string_ssr& str, size_type position=npos) const;
        size_type find_last_of(const std::string& str, size_type position=npos) const;
        size_type find_last_of(const_iterator s, size_type position=npos) const;
        size_type find_last_of(const_iterator s, size_type position, size_type n) const;
        size_type find_last_of(value_type c, size_type position=npos) const;

        size_type find_first_not_of(const string_ssr& str, size_type position=0) const;
        size_type find_first_not_of(const std::string& str, size_type position=0) const;
        size_type find_first_not_of(const_iterator s, size_type position=0) const;
        size_type find_first_not_of(const_iterator s, size_type position, size_type n) const;
        size_type find_first_not_of(value_type c, size_type position=0) const;

        size_type find_last_not_of(const string_ssr& str, size_type position=npos) const;
        size_type find_last_not_of(const std::string& str, size_type position=npos) const;
        size_type find_last_not_of(const_iterator s, size_type position=npos) const;
        size_type find_last_not_of(const_iterator s, size_type position, size_type n) const;
        size_type find_last_not_of(value_type c, size_type position=npos) const;

        /*
         * substr(), compare()函数
        */

        string_ssr substr(size_type position=0, size_type len =npos) const{
            len=changeVarWhenEqualNPOS(len,size(),position);
            return string_ssr(begin()+position,begin()+position+len);
        }
        int compare(const string_ssr str) const;

        int compare(size_type position, size_type len, const string_ssr& str) const;
        int compare(size_type position, size_type len, const string_ssr& str,
                size_type subpos, size_type sublen=npos) const;
        int compare(const_iterator s)const;
        int compare(size_type position, size_type len, const_iterator s) const;
        int compare(size_type position, size_type len, const_iterator s, size_type n) const;

    public:
        //一些友元函数
        friend std::ostream& operator<<(std::ostream& out, const string_ssr& str);
        friend std::istream& operator>>(std::istream& in, string_ssr& str);

        friend string_ssr operator+(const string_ssr& lhs, const string_ssr& rhs);
        friend string_ssr operator+(const string_ssr& lhs, const_iterator rhs);
        friend string_ssr operator+(const_iterator lhs, const string_ssr& rhs);
        friend string_ssr operator+(const string_ssr& lhs, value_type rhs);
        friend string_ssr operator+(value_type lhs, const string_ssr& rhs);

        friend bool operator==(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator==(const string_ssr& lhs, const_iterator rhs);
        friend bool operator==(const_iterator lhs, const string_ssr& rhs);

        friend bool operator!=(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator!=(const string_ssr& lhs, const_iterator rhs);
        friend bool operator!=(const_iterator lhs, const string_ssr& rhs);

        friend bool operator<(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator<(const string_ssr& lhs, const_iterator rhs);
        friend bool operator<(const_iterator lhs, const string_ssr& rhs);

        friend bool operator<=(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator<=(const string_ssr& lhs, const_iterator rhs);
        friend bool operator<=(const_iterator lhs, const string_ssr& rhs);

        friend bool operator>(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator>(const string_ssr& lhs, const_iterator rhs);
        friend bool operator>(const_iterator lhs, const string_ssr& rhs);

        friend bool operator>=(const string_ssr& lhs, const string_ssr& rhs);
        friend bool operator>=(const string_ssr& lhs, const_iterator rhs);
        friend bool operator>=(const_iterator lhs, const string_ssr& rhs);

    };

    template<class InputIterator>
    string_ssr::string_ssr(InputIterator first, InputIterator last) {
        string_ssr_aux(first,last,typename std::is_integral<InputIterator>::type());
    }

    template <class InputIterator>
    string_ssr::iterator string_ssr::insert_aux_copy(iterator position, InputIterator first,
                                                     InputIterator last) {
        size_type lengthOfInsert=distance(last,first);
        auto newCapacity=getNewCapacity(lengthOfInsert);
        iterator newStart=dataAlloc::allocate(newCapacity);
        iterator newfinish=SSRSTL::uninitialized_copy(start_,position,newStart);
        newfinish=SSRSTL::uninitialized_copy(first,last,position);
        auto res=newfinish;
        newfinish=SSRSTL::uninitialized_copy(position,finish_,newfinish);

        destroyAndDeallocate();
        start_=newStart;
        finish_=newfinish;
        endOfStorage_=start_+newCapacity;
        return res;
    }
    
    template<class InputIterator>
    string_ssr::iterator string_ssr::insert(iterator p, InputIterator first, InputIterator last){
        auto lengthOfleft=capacity()-size();
        size_type lengthOfneed=distance(first,last);
        //判断是否需要重新申请内存
        if(lengthOfneed<=lengthOfleft){
            //若不需要重新申请内存
            for(iterator it=finish_-1;it>=p;--it){
                *(it+lengthOfneed)=*it;
            }
            SSRSTL::uninitialized_copy(first,last,p);
            finish_=finish_+lengthOfneed;
            return p+lengthOfneed;
        }else{
            //若需要重新申请内存
            return insert_aux_copy(p,first,last);
        }
    }

    template<class InputIterator>
    //注意返回引用
    string_ssr& string_ssr::append(InputIterator first, InputIterator last){
        insert(end(),first,last);
        return *this;
    }

    template<class InputIterator>
    //注意返回引用
    string_ssr& string_ssr::replace(iterator it1, iterator it2, InputIterator first, InputIterator last){
        auto ptr=erase(it1,it2);
        insert(ptr,first,last);
        return *this;
    }
    
    template<class InputIterator>
    void string_ssr::allocateAndCopy(InputIterator first, InputIterator last){
        auto capacity=distance(first, last);
        start_=dataAlloc::allocate(capacity);
        finish_=SSRSTL::uninitialized_copy(first, last, start_);
        endOfStorage_=start_+capacity;
    }
    
    template<class InputIterator>
    void string_ssr::string_ssr_aux(InputIterator first, InputIterator last, std::false_type){
        allocateAndCopy(first, last);
    }
    
}

#endif //SSRSTL_STRING_SSR_H
