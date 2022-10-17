cmake_minimum_required(VERSION 3.16.3)

project(matrix_calculator LANGUAGES CXX)

add_library(${PROJECT_NAME} src/matrix.cpp  include/matrix_calc)
#target_sources(${PROJECT_NAME} PRIVATE src/matrix.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)

add_executable(main examples/main.cpp)
target_link_libraries(main ${PROJECT_NAME})