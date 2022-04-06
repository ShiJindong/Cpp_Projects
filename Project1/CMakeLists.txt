cmake_minimum_required(VERSION 3.10)
project(project1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/app)
add_executable(project1 main.cpp)
