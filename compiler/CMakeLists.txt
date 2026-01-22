cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(tom_lang VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp src/tokenizer.cpp include/tokenizer.hpp)

add_executable(tom_compiler ${SOURCES})

target_include_directories(tom_compiler PRIVATE include)

