cmake_minimum_required(VERSION 2.6)

project(example_car_lab C)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-fno-strict-aliasing")

# set(SRC car_decoder.c car_encoder.c main.cc tests.cc)
set(SRC car_decoder_lab.c)

add_executable(${PROJECT_NAME} ${SRC})

# target_link_libraries(${PROJECT_NAME} gtest pthread)
