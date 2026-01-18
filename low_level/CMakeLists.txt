cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME "low_level")
project(${PROJECT_NAME})

CMAKE_CXX_STANDARD_REQUIRED

add_executable(task_app main.cpp)
