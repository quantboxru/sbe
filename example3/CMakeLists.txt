cmake_minimum_required(VERSION 2.6)

project(example3)

include_directories(/home/dmitryme/dev/xroad/release/sdk/include)
include_directories(/home/dmitryme/dev/xroad/src/3rd_party/gtest/include)
include_directories(/home/dmitryme/dev/xroad/src/3rd_party/gmock/include)

link_directories(/home/dmitryme/dev/xroad/src/3rd_party/gmock/lib)

add_executable(${PROJECT_NAME} tests.cc proto_encoder.c proto_decoder.c utils.c)
target_link_libraries(${PROJECT_NAME} gmock gmock_main)
