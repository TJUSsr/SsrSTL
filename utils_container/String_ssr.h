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
        typedef SSRSTL::Allocator<char> dataAlloc;

        //静态常量，直接在类内进行初始化
        //npos is a static member constant value with the greatest possible value for an element of type size_t.
        static const size_type  npos=-1;

        //一些私有函数
        void moveData(string_ssr& str);
        size_type getNewCapacity(size_type len) const;

        template <class InputIterator>
        iterator insert_aux_copy(iterator position, InputIterator first, InputIterator last);
        iterator insert_aux_filln(iterator position, size_t n, const value_type& value);

        void string_ssr_aux(size_type n,char c, std::true_type);
        template <class InputIterator>
        void string_ssr_aux(InputIterator first, InputIterator last, std::false_type);

        void allocateAndFillN(size_type n, char c);
        template <class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);

        size_type rfind_aux(const_iterator cit, size_type position, size_type lengthOfS, int cond) const;
        size_type find_aux(const_iterator it, size_type position, size_type lengthOfS, int cond) const;

        int compare_aux(size_type position,size_type len, const_iterator cit, size_type subpos, size_type sublen) const;
        bool isContained(char ch,const_iterator first, const_iterator last) const;

        void destroyAndDeallocate();

    public:
        //无参数构造函数
        string_ssr():start_(0),finish_(0),endOfStorage_(0){};
        //有参数的构造函数
        string_ssr(const string_ssr& str, size_type position, size_type len=npos);
        string_ssr(const char* s);
        string_ssr(const char* s, size_type n);
        string_ssr(size_type n,char c);
        string_ssr(const std::string& str);
        string_ssr(const std::string& str,size_type position, size_type len=npos);
        template <class In>

        //复制构造函数
        string_ssr(const string_ssr&str);
        //移动构造函数
        string_ssr(string_ssr&& str);



    };
}

#endif //SSRSTL_STRING_SSR_H
