cmake_minimum_required(VERSION 3.29)
project(K_MEANS)

set(CMAKE_CXX_STANDARD 20)

add_executable(K_MEANS
        main.cpp
        utils.h
        Iris.cpp
        Iris.h)