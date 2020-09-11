cmake_minimum_required(VERSION 3.9)

# set the project name
project(Tutorial)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "Gomoku/*.cpp")
# add the executable
add_executable(Tutorial Gomoku/test.cpp)