cmake_minimum_required(VERSION 3.5)

add_compile_options(-std=c++11 -O3)

file(GLOB_RECURSE SRCS *.cpp)
add_executable(alphabet ${SRCS})
