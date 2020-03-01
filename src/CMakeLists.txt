project(check-quality LANGUAGES CXX)

set(SOURCES main.cpp utils.cpp)
set(HEADERS utils.h)

add_executable(check-quality ${SOURCES} ${HEADERS})

target_include_directories(check-quality PRIVATE ${Babkin_INCLUDE_DIR})
target_link_libraries(check-quality babkin)
