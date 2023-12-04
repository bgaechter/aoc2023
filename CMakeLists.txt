cmake_minimum_required(VERSION 3.21)
project(aoc2023 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-Wall)
add_compile_options(-Wpedantic)
add_compile_options(-Wextra)
add_subdirectory(src)
