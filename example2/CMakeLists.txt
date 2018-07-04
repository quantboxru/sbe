cmake_minimum_required(VERSION 2.6)

project(example_car_lab C)

add_executable(example2 main.cc tests.cc car_encoder.c car_decoder.c utils.c)
target_link_libraries(example2 gtest)
