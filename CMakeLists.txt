cmake_minimum_required(VERSION 3.5)
project(example VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

add_executable(example main.cpp)

target_include_directories(example PRIVATE single_include/nlohmann)
