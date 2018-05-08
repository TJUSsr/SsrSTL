//
// Created by Administrator on 2018/5/8.
//
#ifndef SSRSTL_TYPETRAITS_H
#define SSRSTL_TYPETRAITS_H

namespace SSRSTL{

    struct _true_type{};
    struct _false_type{};

    template <typename T>
    struct _type_traits{
        //可访问的默认构造函数
        typedef _false_type has_trivial_default_constructor;
        //可访问的默认拷贝构造函数
        typedef _false_type has_trivial_copy_constructor;
        //可访问的赋值运算符
        typedef _false_type has_trivial_assignment_operator;
        //可访问的析构函数
        typedef _false_type has_trivial_destructor;
        /*POD意指Plain Old Data,也就是标量型别
         * 或传统的C struct(传统的C struct只能包含数据成员，不能包含函数成员。也就是所谓的聚合类。
         * POD型别必然包含无意义的ctor/dtor/copy/assignment函数。
        */
        typedef _false_type is_POD_type;
    };


    //针对Cpp内置类型进行特化,针对指针以及内置类型指针进行偏特化
    template<>
    struct _type_traits<bool>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<signed char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<wchar_t>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<short>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned short>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<int>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned int>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned long long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<float>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<double>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long double>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };

    template<class T>
    struct _type_traits<T*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<class T>
    struct _type_traits<const T*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<signed char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const unsigned char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const signed char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
}


#endif //SSRSTL_TYPETRAITS_H
