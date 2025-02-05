cmake_minimum_required(VERSION 3.22)
project(BucketSort VERSION 1.0.0)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Turn warnings way up and treat warnings as errors
  add_compile_options(-Wall -Wextra -Werror -Wshadow -Woverloaded-virtual -Wredundant-decls
    -Wcast-align -Wwrite-strings -Wlogical-op -g
  )
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(LIBRARIES "bucket_sort")

foreach(LIB IN LISTS LIBRARIES)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/${LIB})
    target_link_libraries(app PUBLIC ${LIB})
endforeach()



set(TEST False CACHE BOOL "Whether or not to build tests")

if(TEST)

  find_package(GTest REQUIRED)
  include(GoogleTest)

  enable_testing()

  foreach(LIB IN LISTS LIBRARIES)
      add_subdirectory(${CMAKE_SOURCE_DIR}/test/${LIB})
  endforeach()

endif()

