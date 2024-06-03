cmake_minimum_required(VERSION 3.16)
project(bpt_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(code  memoryriver.h main.cpp bptree.hpp)