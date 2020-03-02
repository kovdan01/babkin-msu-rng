include(GoogleTest)
project(tests LANGUAGES CXX)

set(SOURCES main.cpp)
set(HEADERS)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${Babkin_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE babkin)

target_include_directories(${PROJECT_NAME} PRIVATE ${GTest_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)

gtest_add_tests(TARGET ${PROJECT_NAME})
