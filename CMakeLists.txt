CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(EzHash C)

add_subdirectory(libraries/libft)

file(GLOB SOURCES sources/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(includes)
target_link_libraries(${PROJECT_NAME} ft)
