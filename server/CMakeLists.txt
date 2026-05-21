cmake_minimum_required(VERSION 4.1)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server main.cpp)

target_link_libraries(server ws2_32)