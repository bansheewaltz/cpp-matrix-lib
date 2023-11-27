cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER g++)
project(s21_matrix_oop LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/updateSubmodules.cmake)
add_subdirectory(external)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wextra -Wpedantic")

if(UNIX AND NOT CMAKE_APPLE_SILICON_PROCESSOR)
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
endif()

add_library(${PROJECT_NAME} STATIC src/s21_matrix_oop.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(APPLE)
  target_link_options(${PROJECT_NAME} PUBLIC -ld_classic)
endif()

option(ENABLE_TESTING " Enable testing " ON)

if(ENABLE_TESTING)
  include(CTest)
  add_subdirectory(test)
endif()
