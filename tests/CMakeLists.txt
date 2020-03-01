include(GoogleTest)
project(tests LANGUAGES CXX)

set(SOURCES main.cpp)
set(HEADERS)

add_executable(tests ${SOURCES} ${HEADERS})
target_include_directories(tests PRIVATE ${Babkin_INCLUDE_DIR} ${GTest_INCLUDE_DIR})
target_link_libraries(tests babkin gtest)

gtest_add_tests(TARGET tests)
