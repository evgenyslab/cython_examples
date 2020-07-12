cmake_minimum_required(VERSION 3.0.0)

# Name the C++ class project:
project(CPPInterface)

add_compile_options(-std=c++11)

# add all include directories:
include_directories(
        include
)

add_subdirectory(tests)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h*)

# create static library for custom class:
# add option for interface library only with header files
# add_library(cppInterface INTERFACE)
IF(UNIX)
  IF(APPLE)
    add_library(cppInterface STATIC ${SOURCES})
  ELSE()
    add_library(cppInterface SHARED ${SOURCES})
  ENDIF()
ENDIF()
