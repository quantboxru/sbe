cmake_minimum_required(VERSION 2.6)

project(example_car_lab C)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-arch i386 -fno-strict-aliasing")

# set(SRC car_decoder.c car_encoder.c main.cc tests.cc)
# set(SRC car_codec_lab.c group_size_encoding.c custom_group_size_encoding.c utils.c)
# add_executable(${PROJECT_NAME} ${SRC})

# set(SRC_encoder car_encoder_lab.c utils.c)
# add_executable(car_encoder_lab ${SRC_encoder})

# set(SRC_decoder car_decoder_lab.c utils.c)
# add_executable(car_decoder_lab ${SRC_decoder})

# target_link_libraries(${PROJECT_NAME} gtest pthread)

add_executable(example2 main.cc tests.cc)
target_link_libraries(example2 gtest)
