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
        typedef _false_type has_trivial_default_constructor;
        typedef _false_type has_trivial_copy_constructor;
        typedef _false_type has_trivial_assignment_operator;
        typedef _false_type has_trivial_destructor;
        typedef _false_type is_POD_type;
    };
}


#endif //SSRSTL_TYPETRAITS_H
