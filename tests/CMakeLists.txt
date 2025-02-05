add_executable(linear_sort_test ${CMAKE_CURRENT_SOURCE_DIR}/bucket_sort_test.cpp)

target_link_libraries(linear_sort_test GTest::gtest_main)
target_link_libraries(linear_sort_test linear_sort)

gtest_discover_tests(linear_sort_test)

target_include_directories(linear_sort_test PUBLIC ${CMAKE_SOURCE_DIR}/include)