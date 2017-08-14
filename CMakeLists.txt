cmake_minimum_required(VERSION 3.8)
project(fast_itoa)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES algorithm/itoa.hpp)
set(SOURCE_FILES main.cpp)

add_compile_options(-O3)

add_executable(itoa_benchmark_debug ${SOURCE_FILES} ${HEADER_FILES})

add_executable(itoa_benchmark_nodebug ${SOURCE_FILES} ${HEADER_FILES})
target_compile_options(itoa_benchmark_nodebug PRIVATE -DNDEBUG)