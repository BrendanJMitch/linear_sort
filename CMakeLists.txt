cmake_minimum_required(VERSION 3.22)
project(BucketSort VERSION 1.0.0)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Turn warnings way up and treat warnings as errors
  add_compile_options(-Wall -Wextra -Werror -Wshadow -Woverloaded-virtual -Wredundant-decls
    -Wcast-align -Wwrite-strings -Wlogical-op
  )
endif()

# Allow setting build type (default to Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type: Debug, Release, RelWithDebInfo, MinSizeRel" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
    add_compile_options(-g)
    set(TEST True)
    message(STATUS "Compiling in Debug mode with extra debug symbols")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    add_compile_options(-O3)
    message(STATUS "Compiling in Release mode with optimizations")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
target_link_libraries(app PUBLIC linear_sort)

if(TEST)

  message(STATUS "Compiling tests")
  find_package(GTest REQUIRED)
  include(GoogleTest)

  enable_testing()

  add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

endif()

