cmake_minimum_required(VERSION 3.5)
project(fibutils)

set(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(fibutils STATIC
    prettyTable.cpp
    uptime.cpp
)

target_compile_options(fibutils PRIVATE -ggdb)

ADD_EXECUTABLE(tests tests.cpp)
TARGET_LINK_LIBRARIES(tests fibutils)