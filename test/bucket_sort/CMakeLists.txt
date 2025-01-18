add_executable(bucket_sort_test ${CMAKE_CURRENT_SOURCE_DIR}/bucket_sort_test.cpp)

target_link_libraries(bucket_sort_test GTest::gtest_main)
target_link_libraries(bucket_sort_test bucket_sort)

gtest_discover_tests(bucket_sort_test)

target_include_directories(bucket_sort_test PUBLIC ${CMAKE_SOURCE_DIR}/include/bucket_sort)