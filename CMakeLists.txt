cmake_minimum_required(VERSION 2.6)

project(sbe)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_C_FLAGS "-arch i386 -arch x86_64 -fno-strict-aliasing")
# set(CMAKE_CXX_FLAGS "-arch i386 -arch x86_64 -fno-strict-aliasing")
set(CMAKE_C_FLAGS "-fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "-fno-strict-aliasing")

include_directories(3rdparty/googletest/googletest/include)
add_subdirectory(3rdparty/googletest)
# add_subdirectory(example2)
add_subdirectory(example3)
