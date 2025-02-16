cmake_minimum_required(VERSION 3.10)
project(lib)

set(CMAKE_CXX_STANDARD 17)

add_library(lib SHARED lib.cpp)
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})