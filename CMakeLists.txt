cmake_minimum_required(VERSION 3.22.1)
project(Ray-Tracer)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Ray-Tracer main.cpp)

target_link_libraries(Ray-Tracer sfml-graphics)