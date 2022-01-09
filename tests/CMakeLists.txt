cmake_minimum_required(VERSION 3.5)

project(fibstdTests)

ADD_EXECUTABLE(${PROJECT_NAME}
    main.cpp
    configTemplateTests.cpp
    prettyTableTests.cpp
    uptimeTests.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} fibstd)