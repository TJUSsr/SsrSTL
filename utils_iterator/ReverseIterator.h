//
// Created by monster on 18-5-9.
//
#ifndef SSRSTL_REVERSEITERATOR_H
#define SSRSTL_REVERSEITERATOR_H

#include "Iterator.h"

namespace SSRSTL{
    //反向迭代器,STL源码剖析并没有这部分,结合Github别人的成果进行学习
    //https://github.com/zouxiaohang/TinySTL/blob/master/TinySTL/ReverseIterator.h
    /*
     * 反向迭代器会提供与普通迭代器相反方向的遍历功能。
     * 反向迭代器其实一个正向迭代器的适配器，它的实现都是通过调用正向迭代器的操作.
     * 为了与迭代器的概念保持一致（begin指向迭代器的第一个元素，end指向迭代器的最后一个元素的下一个位置）
     * 又与正向迭代器有一点点不同。
     * 正向迭代器指向的范围是序列中的第一个元素到最后一个元素的下一个位置，
     * 为了保持迭代器概念的统一，
     * 反向迭代器的rbegin应该是序列的最后一个元素，rend应该是第一个元素前面的元素。
     * 所以，在我所设计的calss reverse_iterator_t中，有两个Iterator类型的private成员
     * base_即是正向迭代器所指向的位置，cur_是反向迭代器所指向的位置，为base_-1
     */

    template <typename Iterator>
    class reverse_iterator_t{
    public:
        //基于Iterator产生reverse_iterator_t
        typedef Iterator                                                    iterator_type;
        typedef typename _iterator_traits<Iterator>::iterator_category      iterator_category;
        typedef typename _iterator_traits<Iterator>::value_type             value_type;
        typedef typename _iterator_traits<Iterator>::reference              reference;
        typedef const reference                                             const_reference;
        typedef typename _iterator_traits<Iterator>::pointer                pointer;
        typedef const pointer                                               const_pointer;
        typedef typename _iterator_traits<Iterator>::difference_type        difference_type;

        //构造函数
        reverse_iterator_t();
        //利用explicit拒绝隐式类型转换
        explicit reverse_iterator_t(const iterator_type& it);
        //复制构造函数
        template <typename Ite>
        explicit reverse_iterator_t(const reverse_iterator_t<Ite>& it);;
        //返回base_迭代器
        inline iterator_type Get_base() const;
        //重载*号运算符,非const函数
        reference operator*();
        //重载*号运算符,const函数
        const_reference operator*()const;
        //重载->运算符,非const函数
        pointer operator->();
        //重载->运算符,const函数
        const_pointer operator->()const;
        //重载前置++运算符,注意返回类型位自身类型的引用
        //this是指向reverse_iterator_t类型对象的一个指针,*this返回的是自身引用
        reverse_iterator_t& operator++();
        //重载后置++运算符，返回一个常量
        const reverse_iterator_t operator ++(int);
        //重载前置--运算符，返回一个引用
        reverse_iterator_t& operator--();
        //重载后置--运算符，返回一个常量
        const reverse_iterator_t operator--(int);
        //重载[]运算符
        reference operator[](difference_type n);
        //重载+,+=,-,-=运算符
        reverse_iterator_t  operator+(difference_type n)const;
        reverse_iterator_t& operator+=(difference_type n);
        reverse_iterator_t  operator-(difference_type n)const;
        reverse_iterator_t& operator-=(difference_type n);

        //声明友元函数 双参数+,-,==,!=,>,<,>=,<=
        template<typename Iterator>
        friend reverse_iterator_t<Iterator> operator+(typename reverse_iterator_t<Iterator>::difference_type n,
        const reverse_iterator_t<Iterator>& rev_it);

       template <typename Iterator>
        friend reverse_iterator_t<Iterator> operator-(typename reverse_iterator_t<Iterator>::difference_type n,
        const reverse_iterator_t<Iterator>& rev_it);

        template <typename Iterator>
        friend bool operator==(const reverse_iterator_t<Iterator>& lhs,
                const reverse_iterator_t<Iterator>& rhs);

        template <typename Iterator>
        friend bool operator!=(const reverse_iterator_t<Iterator>& lhs,
                               const reverse_iterator_t<Iterator>& rhs);

        template <typename Iterator>
        friend bool operator>(const reverse_iterator_t<Iterator>& lhs,
                               const reverse_iterator_t<Iterator>& rhs);

        template <typename Iterator>
        friend bool operator<(const reverse_iterator_t<Iterator>& lhs,
                               const reverse_iterator_t<Iterator>& rhs);

        template <typename Iterator>
        friend bool operator>=(const reverse_iterator_t<Iterator>& lhs,
                               const reverse_iterator_t<Iterator>& rhs);
        template <typename Iterator>
        friend bool operator<=(const reverse_iterator_t<Iterator>& lhs,
                               const reverse_iterator_t<Iterator>& rhs);
    private:
        Iterator base_;
        Iterator cur_;

        Iterator advanceNStep(Iterator it, difference_type n,
                              bool right //true +,false
                 );

        Iterator advanceNStep(Iterator it,difference_type n,bidirectional_iterator_tag);
        Iterator advanceNStep(Iterator it,difference_type n,random_access_iterator_tag);
    };

    template<typename Iterator>
    reverse_iterator_t<Iterator>::reverse_iterator_t():base_(nullptr),cur_(nullptr){}

    template<typename Iterator>
    reverse_iterator_t<Iterator>::reverse_iterator_t(const iterator_type &it):base_(it) {
        auto temp=it;
        cur_=--it;
    }
    template<typename Iterator>
    template<typename Ite>
    reverse_iterator_t<Iterator>::reverse_iterator_t(const reverse_iterator_t<Ite> &it) {
        base_= static_cast<reverse_iterator_t<Iterator>>(it.Get_base());
        auto temp=base_;
        cur_=--temp;
    }

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::iterator_type reverse_iterator_t<Iterator>::Get_base() const {
        return base_;
    }

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::reference reverse_iterator_t<Iterator>::operator*() { return (*cur_);}

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::const_reference reverse_iterator_t<Iterator>::operator*() const { return (*cur_);}

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::pointer reverse_iterator_t<Iterator>::operator->() { return &(operator*());}

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::const_pointer reverse_iterator_t<Iterator>::operator->() const { return &(operator*());}

    template<typename Iterator>
    reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator++() {
        --base_;
        --cur_;
        return *this;
    }

    template<typename Iterator>
    const reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator++(int) {
        reverse_iterator_t temp=*this;
        ++(*this);
        return temp;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator--() {
        ++base_;
        ++cur_;
        return *this;
    }

    template<typename Iterator>
    const reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator--(int) {
        reverse_iterator_t temp=*this;
        --(*this);
        return temp;
    }

    template<typename Iterator>
    typename reverse_iterator_t<Iterator>::reference reverse_iterator_t<Iterator>::operator[](reverse_iterator_t::difference_type n) {
        return base_()[-n-1];
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator+(reverse_iterator_t::difference_type n) const {
        auto res=*this;
        res+=n;
        return res;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator+=(reverse_iterator_t::difference_type n) {
        base_=advanceNStep(base_,n, false);
        cur_=advanceNStep(cur_,n, false);
        return *this;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator-(reverse_iterator_t::difference_type n) const {
        auto res=*this;
        res-=n;
        return res;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator-=(reverse_iterator_t::difference_type n) {
        base_=advanceNStep(base_,n,true);
        cur_=advanceNStep(cur_,n,true);
        return *this;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator> operator+(typename reverse_iterator_t<Iterator>::difference_type n, const reverse_iterator_t<Iterator> &rev_it) {
        return rev_it+n;
    }

    template<typename Iterator>
    reverse_iterator_t<Iterator> operator-(long n, const reverse_iterator_t<Iterator> &rev_it) {
        return rev_it-n;
    }

    template<typename Iterator>
    bool operator==(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return lhs.cur_==rhs.cur_;
    }

    template<typename Iterator>
    bool operator!=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return !(lhs.cur_==rhs.cur_);
    }

    template<typename Iterator>
    bool operator>(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return lhs.cur_>rhs.cur_;
    }

    template<typename Iterator>
    bool operator<(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return lhs.cur_<rhs.cur_;
    }

    template<typename Iterator>
    bool operator>=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return !(lhs.cur_<rhs.cur_);
    }

    template<typename Iterator>
    bool operator<=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
        return !(lhs.cur_>rhs.cur_);
    }

    template<typename Iterator>
    Iterator
    reverse_iterator_t<Iterator>::advanceNStep(Iterator it, reverse_iterator_t::difference_type n, bool right) {
        if(!right)
            n=-n;
        return advanceNStep(it,n,iterator_category());
    }

    template<typename Iterator>
    Iterator reverse_iterator_t<Iterator>::advanceNStep(Iterator it, reverse_iterator_t::difference_type n,
                                                        random_access_iterator_tag) {
        it+=n;
        return it;
    }

    template<typename Iterator>
    Iterator reverse_iterator_t<Iterator>::advanceNStep(Iterator it, reverse_iterator_t::difference_type n,
                                                        bidirectional_iterator_tag) {
        if(n>0){
            for(int i=0;i<n;++i){
                it=it+1;
            }
        }else{
            for(int i=0;i<-n;++i){
                it=it-1;
            }
        }
        return it;
    }


}


#endif //SSRSTL_REVERSEITERATOR_H
