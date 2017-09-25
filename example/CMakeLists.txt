cmake_minimum_required(VERSION 2.6)

project(example_utests)

set(SRC car.c main.cc tests.cc)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} gtest pthread)
