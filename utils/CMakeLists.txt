project(utils LANGUAGES CXX)

set(SOURCES utils.cpp)
set(HEADERS utils.h)

add_library(utils ${SOURCES} ${HEADERS})
target_link_libraries(utils babkin)
target_include_directories(utils PRIVATE ${Babkin_INCLUDE_DIR})
