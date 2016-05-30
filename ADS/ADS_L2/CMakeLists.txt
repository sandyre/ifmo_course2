cmake_minimum_required(VERSION 3.5)
project(ADS_L2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h Dijkstra.cpp Dijkstra.h DHeap.cpp DHeap.h)
add_executable(ADS_L2 ${SOURCE_FILES})