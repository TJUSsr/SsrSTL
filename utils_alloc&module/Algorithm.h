//
// Created by Monster on 2018/5/22.
//

#ifndef SSRSTL_ALGORITHM_H
#define SSRSTL_ALGORITHM_H

#include <cstring>
#include <utility>
#include "Allocator.h"
#include "Functional.h"
#include "../utils_container/pair_ssr.h"
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

    /*
     * fill()函数，复杂度O(N)
     */
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T& value){
        for(;first!=last;++first)
            *first=value;
    };
    template <>
    inline void fill<char*,char>(char* first, char* last, const char& value){
        memset(first, static_cast<unsigned char>(value),last-first);
    };
    template <>
    inline void fill<wchar_t*, wchar_t >(wchar_t* first, wchar_t* last, const wchar_t& value){
        memset(first, static_cast<unsigned char>(value),(last-first)* sizeof(wchar_t));
    };
    /*
     * fill_n()函数，复杂度O(N)
     */
    template <class OutputIterator, class T, class Size>
    OutputIterator fill_n(OutputIterator first, Size n, const T&value){
        for(;n>0;--n,++first)
            *first=value;
        return first;
    };
    template <class Size>
    char* fill_n(char* first,Size n, const char&value){
        memset(first, static_cast<unsigned char>(value),n);
        return first+n;
    };
    template <class Size>
    wchar_t* fill_n(wchar_t* first,Size n, const wchar_t&value){
        memset(first, static_cast<unsigned char>(value),n* sizeof(wchar_t));
        return first+n;
    };
    /*
     * min(),max()函数，复杂度O(1),
     * 返回两者的较小值，较大值
     * 注意返回值为常量引用
     */
    template <class T>
    const T& min(const T&a, const T& b){
        return a<b?a:b;
    }
    template <class T, class Compare>
    const T& min(const T&a, const T&b, Compare comp){
        return comp(a,b)?a:b;
    };
    template <class T>
    const T& max(const T&a, const T&b){
        return a<b?b:a;
    }
    template <class T, class Compare>
    const T& max(const T&a, const T&b, Compare comp){
        return  comp(a,b)?b:a;
    };
    /*
     * 堆相关的函数，包括
     * make_heap(),push_heap(),pop_heap(),sort_heap(),is_heap()
     * 注意这些函数均是基于随机存取迭代器的，所以堆的底层可以是支持随机存取的容器
     */
    //******make_heap(),复杂度O(N)******
    //up()函数,head is the header of the heap
    //[first,last]为前闭后闭区间
    template <class RandomAccessIterator, class Compare>
    static void up(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator head, Compare comp){
        if(first!=last){
            //计算last元素的index
            auto index=last-head;
            //基于该元素计算parent的index，这种计算方式认为header的index为0
            auto parentIndex=(index-1)/2;
            for(auto cur=last;parentIndex>=0&&cur!=head;parentIndex=(index-1)/2){
                auto parent=head+parentIndex;
                if(comp(*parent,*cur))
                    SSRSTL::swap(*parent,*cur);
                cur=parent;
                index=cur-head;
            }
        }
    };
    //down()函数
    //[first,last]为前闭后闭区间
    template <class RandomAccessIterator,class Compare>
    static void down(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator head, Compare comp){
        if(first!=last){
            auto index=first-head;
            auto leftChildIndex=index*2+1;
            for(auto cur=first;leftChildIndex<(last-head+1)&&cur<last;leftChildIndex=2*index+1){
                auto child=head+leftChildIndex;
                //有右孩子，且有孩子基于comp比较优于左孩子
                if(child+1<=last&&comp(*child,*(child+1)))
                    child+=1;
                if(comp(*cur,*child))
                    SSRSTL::swap(*cur,*child);
                cur=child;
                index=cur-head;
            }
        }
    };
    /*
     * make_heap()函数，时间复杂度O(N)
     */
    //[first,last)为前闭后开区间，所以这里parent与child之间的计算和up()函数，down()函数不一样
    template <class RandomAccessIterator,class Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        const auto range=last-first;
        //cur指向最后一个parent节点，优于堆是完全二叉树，所以计算出最后一个parent节点之后
        //cur之前的均为parent节点，从后往前对每一个parent节点进行down()操作之后便可以得到一个堆
        for(auto cur=first+range/2-1;cur>=first;--cur){
            SSRSTL::down(cur,last-1,first,comp);
            if(cur==first) return;
        }
    }
    //没有传入Compare时，会默认采用less<>，此时是一个大顶堆
    template <class RandomAccessIterator>
    void make_heap(RandomAccessIterator first,RandomAccessIterator last){
        SSRSTL::make_heap(first,last,typename SSRSTL::less<typename SSRSTL::_iterator_traits<RandomAccessIterator>::value_type>());
    }
    /*
     * push_heap()函数，时间复杂度O(logN)
     */
    template <class RandomAccessIterator, class Compare>
    void push_heap(RandomAccessIterator first,RandomAccessIterator last, Compare comp){
        SSRSTL::up(first,last-1,first,comp);
    }
    template <class RandomAccessIterator>
    void push_heap(RandomAccessIterator first, RandomAccessIterator last){
        SSRSTL::push_heap(first,last-1,first,typename SSRSTL::less<typename SSRSTL::_iterator_traits<RandomAccessIterator>::value_type >());
    }
    /*
     * pop_heap()函数，时间复杂度O(logN)
     */
    template <class RandomAccessIterator, class Compare>
    void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        SSRSTL::swap(*first,*(last-1));
        if(last-first>=2)
            SSRSTL::down(first,last-2,first,comp);
    };
    template <class RandomAccessIterator>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last){
        SSRSTL::pop_heap(first,last,typename SSRSTL::less<typename SSRSTL::_iterator_traits<RandomAccessIterator>::value_type >());
    }
    /*
     * sort_heap()函数，时间复杂度O(N)
     */
    template <class RandomAccessIterator, class Compare>
    void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        for(auto cur=first;first!=last;++cur){
            SSRSTL::pop_heap(first,last,comp);
        }
    };
    template <class RandomAccessIterator>
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last){
        SSRSTL::sort_heap(first,last,typename SSRSTL::less<typename SSRSTL::_iterator_traits<RandomAccessIterator>::value_type >());
    }
    /*
     * is_heap()函数，时间复杂度O(N)
     */
    template <class RandomAccessIterator,class Compare >
    bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
        const auto range=last-first;
        auto index=range/2-1;
        for(auto cur=first+index;cur>=first;--cur,--index){
            if(comp(*cur,*(first+index*2+1))||(first+index*2+2<last)&&comp(*cur,*(first+index*2+2))){
                return false;
            }
            if(cur==first)
                break;
        }
        return true;
    };
    template <class RandomAccessIterator>
    bool is_heap(RandomAccessIterator first, RandomAccessIterator last){
        return SSRSTL::is_heap(first,last,typename SSRSTL::less<typename SSRSTL::_iterator_traits<RandomAccessIterator>::value_type >() );
    }
    /*
     * all_of(),any_of(),none_of()
     */
    /*
     * all_of()函数，需要一个序列，以及一个谓词（即仿函数）
     * 如果这个仿函数作用在这个序列上都为true，则返回true，否则返回false
     */
    template <class InputIterator, class UnaryPredicate>
    bool all_of(InputIterator frst, InputIterator last, UnaryPredicate pred){
        for(;frst!=last;++frst){
            if(!pred(*frst))
                return false;
        }
        return true;
    };
    /*
     * any_of()函数，类似于all_of()函数，
     * 如果序列终有一个为true，则返回true，否则返回false
     */
    template <class InputIterator,class UnaryPredicate>
    bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred){
        for(;first!=last;++first){
            if(pred(*first))
                return true;
        }
        return false;
    };
    /*
     * 类似于all_of(),any_of()函数
     * 如果序列中所有元素返回false，则返回true，否则返回false
     */
    template <class InputIterator, class UnaryPredicate>
    bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred){
        for(;first!=last;++first){
            if(pred(*first))
                return false;
        }
        return true;
    };
    /*
     * for_each(),find(),find_if(),find_if_not(),find_end()
     * find_first_of(),adjacent_find()
     */
    //for_each(), Time Complexity: O(N).
    //*first返回的是引用，所以该函数会改变容器所存放的元素
    template <class InputIterator, class Function>
    Function for_each(InputIterator first, InputIterator last, Function fn){
        for(;first!=last;++first)
            fn(*first);
        return fn;
    };
    //find(), Time Complexity: O(N).
    //返回值是迭代器
    template <class InputIterator, class T>
    InputIterator find(InputIterator first, InputIterator last, const T& value){
        for(;first!=last;++first){
            if(*first==value)
                break;
        }
        return first;
    };
    //find_if(), Time Complexity: O(N)
    template <class InputIterator, class UnaryPredicate>
    InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred){
        for(;first!=last;++first){
            if(pred(*first))
                break;
        }
        return first;
    };
    //find_if_not(), Time Complexity: O(N)
    template <class InputIterator, class UnaryPredicate>
    InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred){
        for(;first!=last;++first){
            if(!pred(*first))
                break;
        }
        return first;
    };
    //find_end(), Time Complexity: O(N^2)
    //在一个序列中搜索出最后一个与另一个序列匹配的字序列
    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                ForwardIterator2 first2, ForwardIterator2 last2){
        if(first2==last2)
            return last1;
        auto ret=last1;
        while(first1!=last1){
            ForwardIterator1 it1=first1;
            ForwardIterator2 it2=first2;
            while(*it1==*it2){
                ++it1;
                ++it2;
                if(it2==last2){
                    ret=first1;
                    break;
                }
                if(it1==last1)
                    return ret;
            }
            ++first1;
        }
        return ret;
    };
    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2,
    BinaryPredicate pred){
        if(first2==last2)
            return last1;
        auto ret=last1;
        while(first1!=last1){
            ForwardIterator1 it1=first1;
            ForwardIterator2 it2=first2;
            while(pred(*it1,*it2)){
                ++it1;++it2;
                if(it2==last2){ret=first1;break;}
                if(it1==last1)
                    return ret;
            }
            ++first1;
        }
        return ret;
    };
    //find_first_of(), Time Complexity: O(N^2).
    //类似于find_end()
    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2){
        if(first2==last2)
            return last1;
        auto ret=last1;
        while(first1!=last1){
            auto it1=first1;
            auto it2=first2;
            while(*it1==*it2){
                ++it1;++it2;
                if(it2==last2||it1==last1)
                    return first1;
            }
            ++first1;
        }
        return ret;
    };
    template <class ForwardIterator1, class ForwardIterator2, class BinayPredicate>
    ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2,
    BinayPredicate pred){
        if(first2==last2)
            return last1;
        auto ret=last1;
        while (first1!=last1){
            auto it1=first1;
            auto it2=first2;
            while (pred(*it1,*it2)){
                ++it1;++it2;
                if(it2==last2||it1==last1)
                    return first1;
            }
            ++first1;
        }
        return ret;
    };
    /*
     * adjacent_find(), Time Complexity: O(N)
     */
    template <class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred){
        for(;first!=last;++first){
            if(first+1!=last&&pred(*first,*(first+1)))
                break;
        }
        return first;
    }
    template <class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
        return adjacent_find(first, last, typename SSRSTL::equal_to<typename SSRSTL::_iterator_traits<ForwardIterator>::value_type >() );
    }
    /*
     * count(),count_if()
     * Time Complexity: O(N)
     */
    template <class InputIterator, class T>
    typename SSRSTL::_iterator_traits<InputIterator>::difference_type count(
            InputIterator first, InputIterator last, const T& value
            ){
        typename SSRSTL::_iterator_traits<InputIterator>::difference_type n=0;
        for(;first!=last;++first){
            if(*first==value)
                ++n;
        }
        return n;
    };
    template <class InputIterator, class UnaryPredicate>
    typename SSRSTL::_iterator_traits<InputIterator>::difference_type count_if(
            InputIterator first, InputIterator last, UnaryPredicate pred
            ){
        typename SSRSTL::_iterator_traits<InputIterator>::difference_type n=0;
        for(;first!=last;++first){
            if(pred(*first))
                ++n;
        }
        return n;
    };
    /*
     * mismatch(), Time Complexity: O(N)
     */
    template <class InputIterator1, class InputIterator2>
    typename SSRSTL::pair_ssr<InputIterator1,InputIterator2> mismatch(
            InputIterator1 first1,InputIterator1 last1,InputIterator2 first2
            ){
        for(;first1!=last1;++first1,++first2){
            if(*first1!=*first2)
                break;
        }
        return SSRSTL::make_pair(first1,first2);
    };
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    typename SSRSTL::pair_ssr<InputIterator1,InputIterator2> mismatch(
            InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred
            ){
        for(;first1!=last1;++first1,++first2){
            if(!pred(*first1,*first2))
                break;
        }
        return SSRSTL::make_pair(first1,first2);
    };
    /*
     * equal(), Time Complexity: O(N)
     */



}

#endif //SSRSTL_ALGORITHM_H
