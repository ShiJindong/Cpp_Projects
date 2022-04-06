cmake_minimum_required(VERSION 3.10)
project(project2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/app)
add_executable(project2 main.cpp)
