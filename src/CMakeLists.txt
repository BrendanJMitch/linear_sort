add_library(linear_sort SHARED ${CMAKE_CURRENT_SOURCE_DIR}/bucket_sort.cpp)

target_include_directories(linear_sort PUBLIC ${CMAKE_SOURCE_DIR}/include)