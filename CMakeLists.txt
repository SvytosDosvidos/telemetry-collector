cmake_minimum_required(VERSION 4.1)
project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(client main.cpp)

target_link_libraries(client ws2_32)