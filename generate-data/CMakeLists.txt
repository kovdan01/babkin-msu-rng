project(generate-data LANGUAGES CXX)

set(SOURCES main.cpp)
set(HEADERS)

add_executable(generate-data ${SOURCES} ${HEADERS})

target_include_directories(generate-data PRIVATE ${Babkin_INCLUDE_DIR} ${Utils_INCLUDE_DIR})
target_link_libraries(generate-data babkin utils)
