#制定Cmake最低版本
cmake_minimum_required(VERSION 3.10)
#工程的名字SsrSTL
project(SsrSTL)
set(CMAKE_CXX_STANDARD 11)

#设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(${PROJET_SOURCE_DIR}/utils_alloc)
add_subdirectory(utils_alloc)

set(SsrSTL main.cpp)

#生成可执行文件
add_executable(SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${SsrSTL})
target_link_libraries(SsrSTL_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} utils_alloc)