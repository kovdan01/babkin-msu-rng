project(utils LANGUAGES CXX)

set(SOURCES utils.cpp)
set(HEADERS utils.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${Babkin_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE babkin)
