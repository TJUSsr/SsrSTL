//
// Created by Monster on 2018/5/23.
//

#ifndef SSRSTL_PAIR_SSR_H
#define SSRSTL_PAIR_SSR_H

#include "../utils_alloc/Algorithm.h"

//设计pair
namespace SSRSTL{
    template <typename T1, typename T2>
    struct pair{
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        //构造函数，复制构造函数，赋值运算符,swap()函数
        pair()= default;
        template <typename U, typename V>
        pair(const pair<U,V>& pr);
        pair(const first_type& f_value, const second_type& s_value);
        pair& operator=(const pair& pr);
        void swap(pair& pr);

        //友元函数，==,!=,<,>,<=,>=运算符
        template <typename T1, typename T2>
        friend bool operator==(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
        template <typename T1, typename T2>
        friend bool operator!=(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
        template <typename T1, typename T2>
        friend bool operator>(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
        template <typename T1, typename T2>
        friend bool operator<(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
        template <typename T1, typename T2>
        friend bool operator>=(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
        template <typename T1, typename T2>
        friend bool operator<=(const pair<T1,T2>& lhs,const pair<T1,T2>& rhs);
    };

    template<typename T1, typename T2>
    template<typename U, typename V>
    pair<T1, T2>::pair(const pair<U, V> &pr):first(pr.first),second(pr.second){}

    template<typename T1, typename T2>
    pair<T1, T2>::pair(const first_type &f_value, const second_type &s_value):first(f_value),second(s_value) {}

    template<typename T1, typename T2>
    pair<T1,T2>& pair<T1, T2>::operator=(const pair &pr) {
        if(this!=&pr){
            first=pr.first;
            second=pr.second;
        }
        return *this;
    }

    template<typename T1, typename T2>
    void pair<T1, T2>::swap(pair &pr) {
        SSRSTL::swap(first,pr.first);
        SSRSTL::swap(second,pr.second);
    }

    template<typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first==rhs.first)&&(lhs.second==rhs.second);
    }

    template<typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs==rhs);
    }

    template<typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first>rhs.first||(lhs.first==rhs.first&&lhs.second>rhs.second);
    }

    template<typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return rhs<lhs;
    }

    template<typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs<rhs);
    }

    template<typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs>rhs);
    }


}

#endif //SSRSTL_PAIR_SSR_H
