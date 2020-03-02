project(check-quality LANGUAGES CXX)

set(SOURCES main.cpp)
set(HEADERS)

add_executable(check-quality ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${Babkin_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE babkin)

target_include_directories(${PROJECT_NAME} PRIVATE ${Utils_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE utils)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)
