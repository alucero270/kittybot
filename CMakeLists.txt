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
  # add_subdirectory(tests) -- uncomment when tests exist (Month 1 Week 4)
endif()

# Modules added here as they're built (Month 1+)
# add_subdirectory(src)
add_library(kittybot
        src/kittybot/version.cpp
        src/kittybot/logger.cpp
)

target_include_directories(kittybot
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_logger
        tests/test_logger.cpp
)

target_link_libraries(test_logger
        PRIVATE
        kittybot
)

add_test(NAME logger_test COMMAND test_logger)