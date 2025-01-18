add_library(bucket_sort SHARED ${CMAKE_CURRENT_SOURCE_DIR}/bucket_sort.cpp)

target_include_directories(bucket_sort PUBLIC ${CMAKE_SOURCE_DIR}/include/bucket_sort)