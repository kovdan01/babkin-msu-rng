cmake_minimum_required(VERSION 3.5)

project(babkin-msu-rng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp babkin.cpp pascal_triangle.cpp)
set(HEADERS babkin.h pascal_triangle.h)

add_executable(generator ${SOURCES} ${HEADERS})
