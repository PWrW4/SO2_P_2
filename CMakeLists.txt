cmake_minimum_required(VERSION 3.12)
project(SO2_P_2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(SO2_P_2 fork.h dining_philosophers.h philosopher.h ui.cpp ui.h)

target_link_libraries(SO2_P_2 ncurses)