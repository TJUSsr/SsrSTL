//
// Created by monster on 18-5-9.
//
#ifndef SSRSTL_REVERSEITERATOR_H
#define SSRSTL_REVERSEITERATOR_H

#include "Iterator.h"

namespace SSRSTL{
    //反向迭代器,STL源码剖析并没有这部分,结合Github别人的成果进行学习
    //https://github.com/zouxiaohang/TinySTL/blob/master/TinySTL/ReverseIterator.h

    template <typename Iterator>
    class reverse_iterator_t{
    public:
        //基于Iterator产生reverse_iterator_t
        typedef Iterator iterator_type;
        typedef typename _iterator_traits<Iterator>::iterator_category      iterator_category;
        typedef typename _iterator_traits<Iterator>::value_type             value_type;
        typedef typename _iterator_traits<Iterator>::reference              reference;
        typedef const reference                                             const_reference;
        typedef typename _iterator_traits<Iterator>::pointer                pointer;
        typedef const pointer                                               const_pointer;
        typedef typename _iterator_traits<Iterator>::difference_type        difference_type;

        //构造函数
        reverse_iterator_t():base_(nullptr),cur_(nullptr){}
        //利用explicit拒绝隐式类型转换
        explicit reverse_iterator_t(const iterator_type& it):base_(it) {
            auto temp=it;
            cur_=--it;
        }
        //复制构造函数
        reverse_iterator_t(const reverse_iterator_t&it);
        //重载*号运算符,非const函数
        reference operator*(){ return (*cur_);}
        //重载*号运算符,const函数
        const_reference operator*()const { return (*cur_);}
        //重载->运算符,非const函数
        pointer operator->(){ return &(operator*());}
        //重载->运算符,const函数
        const_pointer operator->()const { return &(operator*());}
        //重载前置++运算符,注意返回类型位自身类型的引用
        //this是指向reverse_iterator_t类型对象的一个指针,*this返回的是自身引用
        reverse_iterator_t& operator++(){
            --base_;
            --cur_;
            return *this;
        }
        //重载后置++运算符

        //返回base_迭代器
        inline iterator_type Get_base(){ return base_};


    private:
        Iterator base_;
        Iterator cur_;
    };

}


#endif //SSRSTL_REVERSEITERATOR_H
