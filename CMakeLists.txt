#制定Cmake最低版本
cmake_minimum_required(VERSION 3.10)
#工程的名字SsrSTL
project(SsrSTL)
set(CMAKE_CXX_STANDARD 11)
#设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(${PROJET_SOURCE_DIR})

if(WIN32 AND NOT MINGW)
    message("WIN32 编译设置")
elseif(WIN32 AND MINGW)
    message("MINGW 编译设置")
elseif(UNIX AND NOT ANDROID)
    message("UNIX 编译设置")
elseif(ANDROID)
    message("ANDROID 编译设置")
endif()

set(SsrSTL main.cpp
        ssrstl_lib/spdlog/spdlog.h
        utils_logs/logger.h
        utils_logs/logger.cpp
        utils_alloc/alloc.h
        utils_alloc/alloc.cpp
        utils_alloc/Allocator.h
        utils_alloc/Construct.h
        utils_typetraits/Typetraits.h
        utils_iterator/Iterator.h
        utils_iterator/ReverseIterator.h
        utils_container/vector_ssr.h utils_container/vector_ssr.impl.h utils_alloc/uninitializedFunctions.h utils_alloc/Algorithm.h utils_container/pair_ssr.h)

#生成可执行文件
add_executable(SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${SsrSTL})
if(UNIX AND NOT ANDROID)
find_package(Threads)
target_link_libraries (SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${CMAKE_THREAD_LIBS_INIT})
endif()