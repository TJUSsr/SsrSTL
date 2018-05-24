//
// Created by monster on 18-5-9.
//
#ifndef SSRSTL_ITERATOR_H
#define SSRSTL_ITERATOR_H

#include <cstddef>

namespace SSRSTL{

    /*
     * 迭代器的五种型别
     * 输入迭代器,输出迭代器
     *      \      /
     *       *    *
     *      前向迭代器
     *          |
     *          *
     *      双向迭代器
     *          |
     *          *
     *      随机迭代器
     * 迭代器有五个属性可供萃取
     * 1,迭代器型别                      iterator_category
     * 2,所指向的类型                    value_type
     * 3,所指向类型的指针                 pointer
     * 4,所指向类型的引用                 conference
     * 5,迭代器之间的差值类型              difference_type
     */
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag:public input_iterator_tag,output_iterator_tag{};
    struct bidirectional_iterator_tag:public forward_iterator_tag{};
    struct random_access_iterator_tag:public bidirectional_iterator_tag{};

    template<typename T,typename Distance>
    struct input_iterator{
        typedef input_iterator_tag iterator_category;
        typedef T                  value_type;
        typedef T*                 pointer;
        typedef T&                 reference;
        typedef Distance           difference_type;
    };

    struct output_iterator{
        typedef output_iterator_tag       iterator_category;
        typedef void                      value_type;
        typedef void                      pointer;
        typedef void                      reference;
        typedef void                      difference_type;
    };

    template <typename T,typename Distance>
    struct forward_iterator{
        typedef forward_iterator_tag iterator_category;
        typedef T                    value_type;
        typedef T*                   pointer;
        typedef T&                   reference;
        typedef Distance             difference_type;
    };

    template <typename T,typename Distance>
    struct bidirectional_iterator{
        typedef bidirectional_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef Distance                   difference_type;
    };

    template <typename T,typename Distance>
    struct random_access_iterator{
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef Distance                   difference_type;
    };

    //可以依据该模板设计自己需要的迭代器,该模板产生的迭代器可以调用标准库的相关算法
    //Category必须是之前定义的五种型别之一
    template <typename Category, typename T, typename Distance=ptrdiff_t, typename point=T*, typename ref=T& >
    struct iterator{
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef point     pointer;
        typedef ref       reference;
        typedef Distance  difference_type;
    };

    template <typename Iterator>
    struct _iterator_traits{
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::difference_type   difference_type;

    };

    //针对指针常指针进行偏特化,基于此偏特化,原始数组也能看作是一种容器,他们的迭代器就是指针
    template <typename T>
    struct _iterator_traits<T* >{
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef T&                         reference;
        typedef T*                         pointer;
        typedef ptrdiff_t                  difference_type;
    };

    template <typename T>
    struct _iterator_traits<const T* >{
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef const T&                   reference;
        typedef const T*                   pointer;
        typedef ptrdiff_t                  difference_type;
    };

    template <typename Iterator>
    static typename Iterator::iterator_category iterator_Category(const Iterator&){
        typedef typename Iterator::iterator_category iterator_category;
        return iterator_category();
    };

    template <typename Iterator>
    static typename Iterator::value_type* value_Type(const Iterator&){
        typedef typename Iterator::value_type value_type;
        return static_cast<value_type *>(nullptr);
    }
    template <typename Iterator>
    static typename Iterator::difference_type* difference_Type(const Iterator){
        typedef typename Iterator::difference_type difference_type;
        return static_cast<difference_type*>(nullptr);
    };
}



#endif //SSRSTL_ITERATOR_H
