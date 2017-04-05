cmake_minimum_required(VERSION 3.0)

project(stack_test) 

add_compile_options(-O2 -std=c++11 -Wall)

include_directories("../common_source")

set(SOURCES stack.cpp ../common_source/logger.cpp ../common_source/my_exception.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


