cmake_minimum_required(VERSION 3.5)

project(fibutils)

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(${PROJECT_NAME} STATIC
    src/prettyTable.cpp
    src/uptime.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(tests)
