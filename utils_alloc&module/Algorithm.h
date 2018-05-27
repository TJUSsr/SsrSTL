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
            if(comp(*cur,*(first+index*2+1))||((first+index*2+2<last)&&comp(*cur,*(first+index*2+2)))){
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
    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2){
        typedef typename SSRSTL::_iterator_traits<ForwardIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<ForwardIterator2>::value_type value_type2;
        return find_end(first1,last1,first2,last2, SSRSTL::equal_to<value_type1 ,value_type2 >());
    };
    //find_first_of(), Time Complexity: O(N^2).
    //类似于find_end()
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
    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
                                   ForwardIterator2 first2, ForwardIterator2 last2){
        typedef typename SSRSTL::_iterator_traits<ForwardIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<ForwardIterator2>::value_type value_type2;
        return find_first_of(first1,last1,first2,last2,SSRSTL::equal_to<value_type1,value_type2 >());
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
        typedef typename SSRSTL::_iterator_traits<ForwardIterator>::value_type value_type;
        return adjacent_find(first, last, SSRSTL::equal_to<value_type ,value_type >() );
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
    template <class InputIterator1, class InputIterator2>
    typename SSRSTL::pair_ssr<InputIterator1,InputIterator2> mismatch(
            InputIterator1 first1,InputIterator1 last1,InputIterator2 first2
    ){
        typedef typename SSRSTL::_iterator_traits<InputIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<InputIterator2>::value_type value_type2;
        return mismatch(first1,last1,first2, SSRSTL::equal_to<value_type1 ,value_type2 >() );
    };
    /*
     * equal(), Time Complexity: O(N)
     */
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2,
    BinaryPredicate pred){
        for(;first1!=last1;++first1,++first2){
            if(!pred(*first1,*first2))
                return false;
        }
        return true;
    };
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2){
        typedef typename SSRSTL::_iterator_traits<InputIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<InputIterator2>::value_type value_type2;
        return equal(first1,last1,first2,last2, SSRSTL::equal_to<value_type1 ,value_type2 >());
    };
    /*
     * distsance(),Time Complexity: O(N)
     */
    template <class InputIterator>
    typename SSRSTL::_iterator_traits<InputIterator>::difference_type _distance(
            InputIterator first, InputIterator last, SSRSTL::input_iterator_tag
            ){
        typename SSRSTL::_iterator_traits<InputIterator>::difference_type distance=0;
        while(first++!=last)
            ++distance;
        return distance;
    }
    template <class RandomIterator>
    typename SSRSTL::_iterator_traits<RandomIterator>::difference_type _distance(
            RandomIterator first, RandomIterator last, SSRSTL::random_access_iterator_tag
            ){
        return last-first;
    }
    template <class Iterator>
    typename SSRSTL::_iterator_traits<Iterator>::difference_type distance(
            Iterator first, Iterator last
            ){
        typedef typename SSRSTL::_iterator_traits<Iterator>::iterator_category iterator_category;
        return _distance(first,last,iterator_category());
    };
    /*
     * advance(), Time Complexity: O(N)
     */
    namespace {
        template <class Iterator, class Distance>
        void _advance(Iterator& it, Distance n, SSRSTL::input_iterator_tag){
            assert(n>=0);
            while(n--){
                ++it;
            }
        };
        template <class Iterator, class Distance>
        void _advance(Iterator& it, Distance n, SSRSTL::bidirectional_iterator_tag){
            if(n<0){
                while(n++)
                    --it;
            }else{
                while(n--)
                    ++it;
            }
        };
        template <class Iterator, class Distance>
        void _advance(Iterator& it, Distance n, SSRSTL::random_access_iterator_tag){
            if(n<0){
                it-=(-n);
            } else{
                it+=n;
            }
        };
    }
    template <class InputIterator, class Distance>
    void advance(InputIterator&it, Distance n){
        typedef typename SSRSTL::_iterator_traits<InputIterator>::iterator_category iterator_category;
        return SSRSTL::_advance(it,n,iterator_category());
    };
    /*
     * search(), Time Complexity: O(N^2)
     * 在第一个序列中查找第二个序列，返回第一个序列的迭代器
     */
    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                ForwardIterator2 first2, ForwardIterator2 last2,
                BinaryPredicate pred){
        while(first1!=last1){
            auto it1=first1;
            auto it2=first2;
            while(it1!=last1&&it2!=last2){
                if(pred(*it1,*it2)){
                    ++it1;++it2;
                }else{
                    break;
                }
            }
            if(it2==last2)
                return first1;
            if(it1==last1)
                return last1;
            ++first1;
        }
        return last1;
    };
    template <class ForwardIterator1, class ForwardIterator2>
    ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2, ForwardIterator2 last2){
        typedef typename SSRSTL::_iterator_traits<ForwardIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<ForwardIterator2>::value_type value_type2;
        return search(first1,last1,first2,last2,SSRSTL::equal_to<value_type1 ,value_type2 >());
    };

    /*
     * is_permutation(), Time Complexity: O(N^N)
     * 判断两个序列是否为同一元素的不同排列
     */
    template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2, BinaryPredicate pred){
        auto res=SSRSTL::mismatch(first1,last1,first2,pred);
        first1=res.first;first2=res.second;
        if(first1==last1)
            return true;
        auto last2=first2;
        SSRSTL::advance(last2,SSRSTL::distance(first1,last1));
        typedef typename SSRSTL::_iterator_traits<ForwardIterator1>::value_type value_type;
        for(auto it1=first1; it1!=last1;++it1){
            if(SSRSTL::find_if(first1,it1,[&](value_type val){ return pred(val,*it1);})==it1){
                auto n=SSRSTL::count(first2,last2,*it1);
                if(n==0||SSRSTL::count(it1,last1,*it1)!=n)
                    return false;
            }
        }
        return true;
    };
    template <class ForwardIterator1, class ForwardIterator2>
    bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2){
        typedef typename SSRSTL::_iterator_traits<ForwardIterator1>::value_type value_type1;
        typedef typename SSRSTL::_iterator_traits<ForwardIterator2>::value_type value_type2;
        return SSRSTL::is_permutation(first1,last1,first2,SSRSTL::equal_to<value_type1 ,value_type2 >());
    };
    /*
     * generate(),generate_n()
     * Time Complexity: O(N)
     */
    template <class InputIterator, class Function>
    void generate(InputIterator first,InputIterator last,Function func){
        for(;first!=last;++first){
            *first=func;
        }
    };
    /*
     * sort(),Time Complexity: O(NlogN)
     * 快排+插入排序+mid3
     * 通用的sort()要求容器具有随机存取迭代器
     */
    namespace {
        //这里的first，last前闭后开
        template <class RandomIterator, class BinaryPredicate>
        typename SSRSTL::_iterator_traits<RandomIterator>::value_type mid3(
                RandomIterator first, RandomIterator last,
                BinaryPredicate pred
                ){
            auto mid=first+((last-first)>>2);
            if(pred(*mid,*first))
                SSRSTL::swap(*mid,*first);
            if(pred(*(last-1),*mid))
                SSRSTL::swap(*(last-1),*mid);
            if(pred(*mid,*first))
                SSRSTL::swap(*mid,*first);
            auto ret=*mid;
            swap(*mid,*(last-1));
            return ret;
        };

        //插入排序,first,last前闭后开
        template <class RandomIterator,class BinaryPredicate>
        void SsrInsertSort(RandomIterator first, RandomIterator last, BinaryPredicate pred){
            RandomIterator j;
            typename SSRSTL::_iterator_traits<RandomIterator>::value_type temp;
            for(auto it=first+1;it<last;++it){
                temp=*it;
                for(j=it;j>=first&&pred(*it,*j);--j){
                    *(j+1)=*j;
                }
                *j=temp;
            }
        };
    }
    //结合了三点取值以及快排的sort, first,last前闭后开
    template <class RandomIterator, class BinaryPredicate>
    void sort(RandomIterator first,RandomIterator last,
            BinaryPredicate pred){
        if(first>=last)
            return;
        if(last-first<=20)
            SSRSTL::SsrInsertSort(first,last,pred);
        auto mid=SSRSTL::mid3(first,last,pred);
        auto p1=first,p2=last-2;
        while(p1<p2){
            while(pred(*p1,mid)&&p1<p2)++p1;
            while(pred(mid,*p2)&&p1<p2)--p2;
            if(p1<p2)
                SSRSTL::swap(*p1,*p2);
        }
        SSRSTL::swap(*p1,*(last-2));//把最后一个元素放到它应该在的位置
        SSRSTL::sort(first,p1,pred);//递归
        SSRSTL::sort(p1+1,last,pred);
    };
    template <class RandomIterator>
    void sort(RandomIterator first,RandomIterator last){
        typedef typename SSRSTL::_iterator_traits<RandomIterator>::value_type value_type;
        SSRSTL::sort(first,last,SSRSTL::less<value_type >());
    }
    /*
     * copy()函数
     */
    template<class InputIterator, class OutputIterator>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, SSRSTL::_true_type){
        auto dis=SSRSTL::distance(first,last);
        memcpy(result,first,dis*sizeof(*first));
        advance(result,dis);
        return result;
    };
    template <class InputIterator,class OutputIterator>
    OutputIterator __copy(InputIterator first,InputIterator last,OutputIterator result, SSRSTL::_false_type){
        while(first!=last){
            *result=*first;
            ++result;
            ++first;
        }
        return result;
    };
    template <class InputIterator, class OutputIterator, class T>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, T*){
        typedef typename SSRSTL::_type_traits<T>::is_POD_type is_POD;
        return __copy(first,last,result,is_POD());
    };
    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
        return __copy(first,last,result,SSRSTL::value_Type(first));
    };
    template <>
    inline char* copy(char *first, char* last, char*result){
        auto dist=last-first;
        memcpy(result,first,dist* sizeof(*first));
        return result+dist;
    }
    template <>
    inline wchar_t* copy(wchar_t* first, wchar_t* last, wchar_t* result){
        auto dist=last-first;
        memcpy(result,first,dist*sizeof(*first));
        return result+dist;
    }

}

#endif //SSRSTL_ALGORITHM_H
