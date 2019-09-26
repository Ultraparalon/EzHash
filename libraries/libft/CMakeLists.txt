CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(ft)

file(GLOB SOURCES *.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC includes)
