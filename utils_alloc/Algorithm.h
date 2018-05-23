//
// Created by Monster on 2018/5/22.
//

#ifndef SSRSTL_ALGORITHM_H
#define SSRSTL_ALGORITHM_H

#include <cstring>
#include <utility>
#include "Allocator.h"
#include "../utils_iterator/Iterator.h"
#include "../utils_typetraits/Typetraits.h"

/*
 * 该头文件内，定义一些常见的容器算法，
 * swap(),
 * fill(),fill_n(),min(),max(),
 * make_heap(),push_heap(),pop_heap(),sort_heap(),is_heap(),
 * all_of(),any_of(),none_of(),for_each()
 * find(),find_if(),find_if_not(),find_end(),find_first_of(),adjacent_find()
 * count(),count_if(),mismatch(),equal(),is_permutation(),
 * search(),advance(),sort(),
 * generate(),generate_n(),
 * distance(),copy().
 */

namespace SSRSTL{
    //****swap()函数*****
    template <typename T>
    void swap(T&a, T&b){
        T temp=a;
        a=b;
        b=temp;
    }

}

#endif //SSRSTL_ALGORITHM_H
