cmake_minimum_required(VERSION 3.20)
project (ai_sieve LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(ai_sieve main.cpp)
target_include_directories(ai_sieve PRIVATE openai-cpp/include/openai)
target_link_libraries(ai_sieve PRIVATE curl)
