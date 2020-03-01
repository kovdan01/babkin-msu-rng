cmake_minimum_required(VERSION 3.5)

project(babkin-msu-rng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd_party)

set(GTest_ROOT_DIR ${THIRD_PARTY_DIR}/GTest)
set(GTest_INCLUDE_DIR ${GTest_ROOT_DIR}/googletest/include)
add_subdirectory(${GTest_ROOT_DIR})

set(Babkin_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/babkin)
set(Babkin_INCLUDE_DIR ${Babkin_ROOT_DIR})
add_subdirectory(${Babkin_ROOT_DIR})

add_subdirectory(src)
add_subdirectory(tests)
