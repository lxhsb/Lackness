cmake_minimum_required(VERSION 3.6)
project(SimpleSelectSocketServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SelectSocketServer.cpp SelectSocketServer.h)
add_executable(SimpleSelectSocketServer ${SOURCE_FILES})