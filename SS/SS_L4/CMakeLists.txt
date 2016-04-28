cmake_minimum_required(VERSION 3.5)
project(SS_L4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(SS_L4 ${SOURCE_FILES})