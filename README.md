# SsrSTL
## Introduction
阅读了[STL源码剖析](https://baike.baidu.com/item/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90/3080024?fr=aladdin)之后，采用C++11实现一个简易的STL标准库，同时练习C++模版编程，加深对STL的理解。

本项目代码均由本人自行编写，但是能力有限，参考[STL源码剖析](https://baike.baidu.com/item/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90/3080024?fr=aladdin)的同时，也在Github，百度，Google上搜索资料，参考了许多其他人的代码，不断提升自己水平。同时在这个过程中，复习总结C++相关知识点。

Life is Hard，Peace.

且行且学习

## 项目简介
### 开发环境
IDE：CLion

编译环境：Mac OS X 10.13.3

### 开发计划
1. STL的一些基本组件，包括空间配置起，迭代器，反向迭代器，萃取等
2. STL中的大部分算饭
3. STL中的一些典型容器，包括vector, list, string, map, unordered_map等
4. 一些有意思的容器，包括但不限于circular buffer, bitmap, skip list, LRU cache, k-d tree, B-tree等

### 完成进度

* 基本组件
    - [x] 空间配置起
    - [x] 迭代器，反向迭代器
    - [x] 迭代器萃取，数据类型萃取 
    - [x] [SPDLOG](https://github.com/gabime/spdlog)
    - [x] vector
    - [ ] string
    - [ ] priotity_queue
    - [ ] stack
    - [ ] deque
    - [ ] queue
    - [x] pair
    - [ ] list
    - [ ] set
    - [ ] multiset
    - [ ] unordered_set
    - [ ] unordered_multiset
    - [ ] map
    - [ ] multimap
    - [ ] unordered_map
    - [ ] unordered_multimap
    - [ ] unique_ptr
    - [ ] shared_ptr
    - [ ] weak_ptr
* STL算法
    - [x] fill, fill_n, copy
    - [x] find, find_if, find_if_not, adjacent_find, search
    - [x] all_of, any_of, none_of
    - [x] is_heap, make_heap, push_heap, pop_heap, sort_heap
    - [x] swap
    - [x] min, max
    - [x] count, count_if
    - [x] mismatch, equal, is_permutation
    - [x] advance, distance, 
    - [x] sort
    - [x] generate, generate_n
* Interesting Containers
    - [ ] circular_buffer
    - [ ] bitmap
    - [ ] binary_search_tree
    - [ ] avl_tree
    - [ ] suffix_array
    - [ ] directed_graph
    - [ ] trie tree
    - [ ] Disjoint-set data structure