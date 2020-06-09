cmake_minimum_required(VERSION 3.0.0)

# Name the C++ class project:
project(CythonWrapper)


add_compile_options(-std=c++11)

# add all include directories:
include_directories(
        include
)

# create static library for custom class:
add_library(CythonWrapper STATIC src/myClass.cpp)
