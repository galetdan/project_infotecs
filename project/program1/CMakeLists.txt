cmake_minimum_required(VERSION 3.10)
project(program1)

set(CMAKE_CXX_STANDARD 17)

add_executable(program1 main.cpp)
target_link_libraries(program1 PRIVATE lib)