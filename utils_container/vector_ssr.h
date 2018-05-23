//
// Created by monster on 18-5-12.
//

#ifndef SSRSTL_VECTOR_SSR_H
#define SSRSTL_VECTOR_SSR_H

#include "../utils_alloc&module/Allocator.h"
#include "../utils_iterator/Iterator.h"
#include "../utils_iterator/ReverseIterator.h"

namespace SSRSTL{
    /*
     * vector容器,需要一块连续的内存,拥有随机存取迭代器
     */
    template <typename T, class Alloc=Allocator<T>>
    class vector_ssr{
    public:
        void set_to_nullptr(){
            start_= nullptr;
            finish_= nullptr;
            endOfStorage_= nullptr;
        };
    private:
        T* start_;
        T* finish_;
        T* endOfStorage_;
        typedef Alloc dataAlloc;
    public:
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef const T*                            const_pointer;
        typedef T*                                  iterator;
        typedef const T*                            const_iterator;
        typedef T&                                  reference;
        typedef const T&                            const_reference;
        typedef reverse_iterator_t<iterator>        reverse_iterator;
        typedef reverse_iterator_t<const_iterator>  const_reverse_iterator;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

        vector_ssr():start_(nullptr),finish_(nullptr),endOfStorage_(nullptr){};

        explicit vector_ssr(const size_type& n);

        vector_ssr(const size_type& n, const value_type& value);

        template <class InputIterator>
        vector_ssr(const InputIterator& first,const InputIterator& last);
        //复制构造函数
        vector_ssr(const vector_ssr& v);
        //移动语义构造函数
        vector_ssr(vector_ssr&& v);
        //赋值运算符
        vector_ssr& operator=(const vector_ssr& v);
        //移动予以运算符
        vector_ssr& operator=(vector_ssr&& v);
        //设置成虚函数,考虑到后面会设计线程安全的vector,可以继承该vector_ssr实现多态
        ~vector_ssr();

        //重载比较运算符,声明比较运算符友元函数
        bool operator==(const vector_ssr& v) const;

        bool operator!=(const vector_ssr& v) const;

        template <typename T, class Alloc=Allocator<T>>
        friend bool operator==(const vector_ssr<T,Alloc>& lhs, const vector_ssr<T,Alloc> rhs);

        template <typename T, class Alloc=Allocator<T>>
        friend bool operator==(const vector_ssr<T,Alloc>& lhs, const vector_ssr<T,Alloc> rhs);

        /*
         * 迭代器相关的函数
         */
        //常成员函数只能调用常成员函数,常量对象只能调用常成员函数
        iterator begin() { return start_;}
        //设计成常成员函数保证返回常量指针不会改变容器内的值
        //常量指针无法赋值给一般指针,一般指针可以赋值给常量指针
        //同样常量引用无法赋值给一般引用,一般引用可以赋值给常量引用
        const_iterator begin() const { return start_;}
        //cbegin()函数要求返回常量指针,所以可以直接设置成常成员函数
        const_iterator cbegin() const { return start_;}
        iterator end() { return finish_;}
        const_iterator end() const { return finish_;}
        const_iterator cend() const{ return finish_;}
        reverse_iterator rbegin(){return reverse_iterator(finish_);}
        const_reverse_iterator rbegin()const {return const_reverse_iterator(finish_);}
        const_reverse_iterator crbegin() const{return const_reverse_iterator(finish_);}
        reverse_iterator rend(){ return reverse_iterator(start_);}
        const_reverse_iterator rend() const{ return const_reverse_iterator(start_);}
        const_reverse_iterator credn() const { return const_reverse_iterator(start_);}
        iterator endOfStorage() { return endOfStorage_;}
        const_pointer endOfStorage()const { return endOfStorage_;}
        const_pointer cendOfStorage()const { return endOfStorage_;}

        /*
         * 访问元素相关的函数,重载[]运算符,front(),back()函数
         */
        reference operator[](const difference_type& i){ return *(start_+i);}
        const_reference operator[](const difference_type& i) const {return *(start_+i);}
        reference front(){ return *start_;}
        const_reference front() const{ return *start_;}
        reference back(){ return *(finish_-1);}
        const_reference back()const{ return *(finish_-1);}
        pointer data(){ return start_;}
        const_pointer data() const { return start_;}

        /*
         * 容量相关的函数,size(),capacity(),empty(),resize(),reserve(),shrink_to_fit()函数
         */
        difference_type size()const{ return finish_-start_;}
        difference_type capacity()const{ return endOfStorage_-start_;}
        bool empty() const{ return start_==finish_;}
        //resize函数,第二个形参有默认值
        void resize(size_type n, value_type value = value_type());
        void reserve(size_type n);

        /*
         * 修改容器相关的函数,push_back(),pop_back(),insert(),swap(),clear();erase()函数
         */
        //清空容器，使size()为0，但是capacity()不变
        void clear();
        void swap(vector_ssr& v);
        void push_back(const value_type& value);
        void pop_back();
        iterator insert(iterator position, const value_type& value);
        void insert(iterator position, const size_type& n, const value_type& value);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);

        //容器的空间配置器相关
        Alloc get_allocator(){ return dataAlloc();}

    private:
        //用来析构以及释放内存
        void destroyAndDeallocate();
        //用来申请内存并且构造
        void allocAndFillN(const size_type& n,const value_type& value);
        //接受迭代器参数，产生一个vector()
        template <class InputIterator>
        void allocAndCopy(const InputIterator& first,const InputIterator& last);

        template <class InputIterator>
        void vector_aux(const InputIterator& first, const InputIterator last, std::false_type);

        template <class Integer>
        void vector_aux(const Integer& n,  const value_type& value, std::true_type);

        template <class InputIterator>
        void insert_aux(iterator position, const InputIterator& first, const InputIterator& last, std::false_type);

        template <class Integer>
        void insert_aux(iterator position, const Integer& n, const value_type& value, std::true_type);

        template <class InputIterator>
        void reallocAndCopy(iterator position, const InputIterator& first, const InputIterator last);

        void reallocAndCopy(iterator position, const size_type& n, const value_type& val);
    };



#include "vector_ssr.impl.h"

}


#endif //SSRSTL_VECTOR_SSR_H
