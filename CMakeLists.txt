cmake_minimum_required(VERSION 3.16.3)
project(matrix_calculator LANGUAGES CXX)

option(BUILD_EXAMPLE_1 "Build executable example #1." ON)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if (BUILD_EXAMPLE_1)
    add_executable(example_1 examples/example_1.cpp)
    target_link_libraries(example_1 ${PROJECT_NAME})
endif ()

add_subdirectory(test)
