cmake_minimum_required(VERSION 3.10)
project(program2)

set(CMAKE_CXX_STANDARD 17)

add_executable(program2 main.cpp)
target_link_libraries(program2 PRIVATE lib)