cmake_minimum_required(VERSION 3.0)

project(array_test) 

add_compile_options(-O2 -std=c++11 -Wall)

include_directories("../common_source")

set(SOURCES array.cpp ../common_source/my_exception.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


