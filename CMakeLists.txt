cmake_minimum_required(VERSION 3.10)

project(LinkedList VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
add_subdirectory(src)
add_subdirectory(tests)
