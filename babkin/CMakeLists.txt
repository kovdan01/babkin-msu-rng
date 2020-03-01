project(babkin LANGUAGES CXX)

set(SOURCES babkin.cpp pascal_triangle.cpp)
set(HEADERS babkin.h pascal_triangle.h)

add_library(babkin ${SOURCES} ${HEADERS})
