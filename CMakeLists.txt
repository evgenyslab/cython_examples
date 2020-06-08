cmake_minimum_required(VERSION 3.0.0)
project(CythonWrapper)
add_compile_options(-std=c++11)

include_directories(
        include
)

add_library(CythonWrapper STATIC src/myClass.cpp)
