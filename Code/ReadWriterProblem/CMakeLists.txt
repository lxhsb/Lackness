cmake_minimum_required(VERSION 3.6)
project(ReadWriterProblem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
add_executable(ReadWriterProblem ${SOURCE_FILES})