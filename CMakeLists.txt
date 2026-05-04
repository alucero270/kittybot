cmake_minimum_required(VERSION 3.25)

project(kittybot
  VERSION 0.1.0
  DESCRIPTION "C++23 companion robot runtime"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Testing
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

add_subdirectory(src)
