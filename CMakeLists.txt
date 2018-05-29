#制定Cmake最低版本
cmake_minimum_required(VERSION 3.10)
#工程的名字SsrSTL
project(SsrSTL)
set(CMAKE_CXX_STANDARD 11)
#设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(${PROJET_SOURCE_DIR})

if(WIN32 AND NOT MINGW)
    message("WIN32 AND NOT MINGW")
elseif(WIN32 AND MINGW)
    message("MINGW AND MINGW")
elseif(UNIX AND NOT ANDROID)
    message("UNIX AND NOT ANDROID")
elseif(ANDROID)
    message("ANDROID")
endif()

set(SsrSTL main.cpp
        ssrstl_lib/spdlog/spdlog.h
        utils_logs/logger.h
        utils_logs/logger.cpp
        utils_alloc&module/alloc.h
        utils_alloc&module/alloc.cpp
        utils_alloc&module/Allocator.h
        utils_alloc&module/Construct.h
        utils_typetraits/Typetraits.h
        utils_iterator/Iterator.h
        utils_iterator/ReverseIterator.h
        utils_container/vector_ssr.h utils_container/vector_ssr.impl.h
        utils_alloc&module/uninitializedFunctions.h
        utils_alloc&module/Algorithm.h utils_container/pair_ssr.h
        utils_alloc&module/Functional.h utils_test/TestUtil.h
        utils_test/VectorTest.h utils_test/VectorTest.cpp
        utils_benchmarkassist/BenchmarkAssist.h
        utils_benchmarkassist/BenchmarkAssist.cpp utils_container/string_ssr.h utils_container/string_ssr.cpp utils_container/avltree_ssr.h utils_container/binarysearchtree_ssr.h utils_container/bitmap_ssr.h utils_othercontainer/cirularbuffer_ssr.h utils_container/deque_ssr.h utils_container/graph_ssr.h utils_container/list_ssr.h utils_smartpointer/shared_ptr_ssr.h utils_smartpointer/weak_ptr_ssr.h utils_smartpointer/unique_ptr_ssr.h utils_container/queue_ssr.h utils_container/stack_ssr.h utils_othercontainer/suffix_array_ssr.h utils_othercontainer/trietree_ssr.h utils_othercontainer/ufset_ssr.h utils_container/unordered_set__ssr.h utils_container/avltree_ssr.impl.h utils_container/binarysearchtree_ssr.impl.h utils_container/bitmap_ssr.impl.h utils_container/circularbuffer_ssr.impl.h utils_container/deque_ssr.impl.h utils_container/graph_ssr.impl.h utils_container/list_ssr.impl.h utils_container/unordered_set_ssr.impl.h utils_test/AvlTreeTest.h utils_test/AvlTreeTest.cpp utils_test/AlgorithmTest.h utils_test/AlgorithmTest.cpp utils_test/BinarySearchTreeTest.h utils_test/BinarySearchTreeTest.cpp utils_test/BitMapTest.h utils_test/BitMapTest.cpp utils_test/CircularBufferTest.h utils_test/CircularBufferTest.cpp utils_test/DequeTest.h utils_test/DequeTest.cpp utils_test/GraphTest.h utils_test/GraphTest.cpp utils_test/ListTest.h utils_test/ListTest.cpp)

#生成可执行文件
add_executable(SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${SsrSTL})
if(UNIX AND NOT ANDROID)
    find_package(Threads)
    target_link_libraries (SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${CMAKE_THREAD_LIBS_INIT})
elseif(WIN32 AND MINGW)
    find_package(psapi)
    target_link_libraries (SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} psapi)
endif()