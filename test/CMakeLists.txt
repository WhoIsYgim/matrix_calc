project(test_matrix_lib)
find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES "*.cpp")



add_executable(${PROJECT_NAME} ${TEST_SOURCES})


target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} PUBLIC matrix_calculator)

gtest_discover_tests(${PROJECT_NAME})
