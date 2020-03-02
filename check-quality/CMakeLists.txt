project(check-quality LANGUAGES CXX)

set(SOURCES main.cpp)
set(HEADERS)

add_executable(check-quality ${SOURCES} ${HEADERS})

target_include_directories(check-quality PRIVATE ${Babkin_INCLUDE_DIR} ${Utils_INCLUDE_DIR})
target_link_libraries(check-quality babkin utils)
