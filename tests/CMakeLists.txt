cmake_minimum_required(VERSION 3.5)

project(${CMAKE_PROJECT_NAME}UnitTests)

ADD_EXECUTABLE(${PROJECT_NAME}
    source/main.cpp
    # tests/.templateTests.cpp
    tests/bitfieldTests.cpp
    tests/byteswapTests.cpp
    tests/configTemplateTests.cpp
    tests/castTests.cpp
    tests/prettyTableTests.cpp
    tests/uptimeTests.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_PROJECT_NAME})