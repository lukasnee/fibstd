cmake_minimum_required(VERSION 3.5)

project(fibutilsTests)

set(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(${PROJECT_NAME}
    main.cpp
    configTemplateTests.cpp
    prettyTableTests.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -O3 #-ggdb
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} fibutils)