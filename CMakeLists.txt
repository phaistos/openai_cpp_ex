cmake_minimum_required(VERSION 3.20)
project (sample1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(sample1 main.cpp)
target_include_directories(sample1 PRIVATE openai-cpp/include/openai)
target_link_libraries(sample1 PRIVATE curl)
