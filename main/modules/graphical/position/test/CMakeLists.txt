cmake_minimum_required (VERSION 3.19)

set (SOURCES "Main.cpp")

project ("position-test")

add_executable (${PROJECT_NAME} ${SOURCES})

add_test (NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries (${PROJECT_NAME}
  PUBLIC
    gtest
    position
)
