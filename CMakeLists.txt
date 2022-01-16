cmake_minimum_required(VERSION 3.5)

project(libfibstd)

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(${PROJECT_NAME} STATIC
    source/prettyTable.cpp
    source/uptime.cpp
)

add_compile_options(
    -Wall -Wextra -O3 #-ggdb
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)
