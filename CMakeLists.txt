cmake_minimum_required(VERSION 3.5)

project(fibstd)

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(${PROJECT_NAME} STATIC
    src/prettyTable.cpp
    src/uptime.cpp
)

add_compile_options(
    -Wall -Wextra -O3 #-ggdb
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(tests)
