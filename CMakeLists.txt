cmake_minimum_required(VERSION 3.5)
project(ISO_19794_2_2005_converter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ISO_19794_2_2005_converter ${SOURCE_FILES})