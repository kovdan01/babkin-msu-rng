cmake_minimum_required(VERSION 3.5)

project(babkin-msu-rng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd_party)

find_package(GTest REQUIRED)
find_package(Boost COMPONENTS COMPONENTS program_options REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP REQUIRED)

set(Babkin_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/babkin)
set(Babkin_INCLUDE_DIR ${Babkin_ROOT_DIR})
add_subdirectory(${Babkin_ROOT_DIR})

set(Utils_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/utils)
set(Utils_INCLUDE_DIR ${Utils_ROOT_DIR})
add_subdirectory(${Utils_ROOT_DIR})

add_subdirectory(check-quality)
add_subdirectory(generate-data)
add_subdirectory(tests)
