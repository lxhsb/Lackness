cmake_minimum_required(VERSION 3.6)
project(SimpleServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(SimpleServer ${SOURCE_FILES})