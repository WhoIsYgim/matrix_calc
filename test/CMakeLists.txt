project(test)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} Test.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)
target_link_libraries(${PROJECT_NAME} PUBLIC matrix_calculator)