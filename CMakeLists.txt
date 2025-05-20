cmake_minimum_required(VERSION 3.30.5)
project(DAProject2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DAProject2
        csvparsing.cpp
        algorithms.h
        algorithms.cpp
        main.cpp
        algorithms_runner.cpp)
