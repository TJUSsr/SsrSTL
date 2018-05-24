//
// Created by Monster on 2018/5/23.
//

#ifndef SSRSTL_PAIR_SSR_H
#define SSRSTL_PAIR_SSR_H

#include "../utils_alloc&module/Algorithm.h"

//设计pair
namespace SSRSTL{
    //声明一下swap()函数
    template <typename T>
    void swap(T&a, T&b);


    template <typename T1, typename T2>
    struct pair_ssr{
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        //构造函数，复制构造函数，赋值运算符,swap()函数
        pair_ssr()= default;
        template <typename U, typename V>
        pair_ssr(const pair_ssr<U,V>& pr);
        pair_ssr(const first_type& f_value, const second_type& s_value);
        pair_ssr& operator=(const pair_ssr& pr);
        void swap(pair_ssr& pr);

        //友元函数，==,!=,<,>,<=,>=运算符
        template <typename U, typename V>
        friend bool operator==(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
        template <typename U, typename V>
        friend bool operator!=(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
        template <typename U, typename V>
        friend bool operator>(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
        template <typename U, typename V>
        friend bool operator<(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
        template <typename U, typename V>
        friend bool operator>=(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
        template <typename U, typename V>
        friend bool operator<=(const pair_ssr<U,V>& lhs,const pair_ssr<U,V>& rhs);
    };

    template<typename T1, typename T2>
    template<typename U, typename V>
    pair_ssr<T1, T2>::pair_ssr(const pair_ssr<U, V> &pr):first(pr.first),second(pr.second){}

    template<typename T1, typename T2>
    pair_ssr<T1, T2>::pair_ssr(const first_type &f_value, const second_type &s_value):first(f_value),second(s_value) {}

    template<typename T1, typename T2>
    pair_ssr<T1,T2>& pair_ssr<T1, T2>::operator=(const pair_ssr &pr) {
        if(this!=&pr){
            first=pr.first;
            second=pr.second;
        }
        return *this;
    }

    template<typename T1, typename T2>
    void pair_ssr<T1, T2>::swap(pair_ssr<T1,T2> &pr) {
        SSRSTL::swap(first,pr.first);
        SSRSTL::swap(second,pr.second);
    }

    template<typename T1, typename T2>
    bool operator==(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return (lhs.first==rhs.first)&&(lhs.second==rhs.second);
    }

    template<typename T1, typename T2>
    bool operator!=(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return !(lhs==rhs);
    }

    template<typename T1, typename T2>
    bool operator>(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return lhs.first>rhs.first||(lhs.first==rhs.first&&lhs.second>rhs.second);
    }

    template<typename T1, typename T2>
    bool operator<(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return rhs<lhs;
    }

    template<typename T1, typename T2>
    bool operator>=(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return !(lhs<rhs);
    }

    template<typename T1, typename T2>
    bool operator<=(const pair_ssr<T1, T2> &lhs, const pair_ssr<T1, T2> &rhs) {
        return !(lhs>rhs);
    }
    /*
     * make_pair()
     */
    template <class U, class V>
    SSRSTL::pair_ssr<U,V> make_pair(const U& u, const V& v){
        return pair_ssr<U,V>(u,v);
    };

}

#endif //SSRSTL_PAIR_SSR_H
