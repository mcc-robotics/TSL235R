cmake_minimum_required(VERSION 3.6)
project(TSL235R)

include(CMakeListsPrivate.txt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    TSL235R.cpp
    TSL235R.h)

add_executable(TSL235R ${SOURCE_FILES})