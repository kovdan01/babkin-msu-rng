project(babkin LANGUAGES CXX)

set(SOURCES babkin.cpp)
set(HEADERS babkin.h pascal_triangle.h)

add_library(babkin ${SOURCES} ${HEADERS})
target_link_libraries(babkin gmp)
target_include_directories(babkin PRIVATE ${GMP_INCLUDE_DIR})
