cmake_minimum_required(VERSION 3.24)
project(map)

set(CMAKE_CXX_STANDARD 17)

add_executable(map main.cpp exceptions.hpp map.hpp utility.hpp)
