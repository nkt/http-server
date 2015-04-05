cmake_minimum_required(VERSION 3.1)
project(http-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Werror -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(BEFORE include)

set(SOURCE_FILES main.cpp)
add_executable(http-server ${SOURCE_FILES})
