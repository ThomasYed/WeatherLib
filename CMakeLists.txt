cmake_minimum_required(VERSION 3.5)
project(example VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wextra -Werror)

add_executable(example weather_library.cpp main.cpp )

find_package(CURL REQUIRED)
target_include_directories(example PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(example PRIVATE ${CURL_LIBRARIES})

target_include_directories(example PRIVATE single_include/nlohmann)
