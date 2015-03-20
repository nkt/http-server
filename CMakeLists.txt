cmake_minimum_required(VERSION 3.1)
project(http-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(BEFORE include)

set(SOURCE_FILES main.cpp src/server.cpp src/request.cpp src/response.cpp)
add_executable(http-server ${SOURCE_FILES})