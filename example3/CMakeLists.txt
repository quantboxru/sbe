cmake_minimum_required(VERSION 2.6)

project(example3)

add_executable(${PROJECT_NAME} main.cc tests.cc proto_encoder.c proto_decoder.c utils.c)
target_link_libraries(${PROJECT_NAME} gtest)
