project(babkin LANGUAGES CXX)

set(SOURCES babkin.cpp)
set(HEADERS babkin.h pascal_triangle.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${GMP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE gmp)
