//
// Created by Monster on 2018/5/24.
//

#ifndef SSRSTL_FUNCTIONAL_H
#define SSRSTL_FUNCTIONAL_H
/*
 * 设计STL过程中会用到的一些仿函数
 */
namespace SSRSTL{

    //小于仿函数
    template <class T>
    struct less{
        typedef T           first_argument_type;
        typedef T           second_argument_type;
        typedef bool        result_type;
        result_type operator()(const first_argument_type& f_value, const second_argument_type& s_value){
            return f_value<s_value;
        }
    };
    //等于仿函数
    template <class T>
    struct equal_to{
        typedef T           first_argument_type;
        typedef T           second_argument_type;
        typedef bool        result_type;
        result_type operator()(const first_argument_type& f_value, const second_argument_type& s_value){
            return f_value==s_value;
        }
    };
}

#endif //SSRSTL_FUNCTIONAL_H
