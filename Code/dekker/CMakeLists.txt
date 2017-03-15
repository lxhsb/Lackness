cmake_minimum_required(VERSION 3.6)
project(dekker)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
set(SOURCE_FILES main.cpp)
add_executable(dekker ${SOURCE_FILES})