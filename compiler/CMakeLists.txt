cmake_minimum_required(VERSION 4.2)

project(tom_lang VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES src/main.cpp)

add_executable(tom_compiler ${SOURCES})

target_include_directories(tom_compiler PRIVATE include)

