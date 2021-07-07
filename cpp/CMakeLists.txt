cmake_minimum_required(VERSION 3.15)
project(playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE 3rdparty/catch2)

add_library(playground playground.cpp)
target_include_directories(playground PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(playground_test tests/test_playground.cpp)
target_link_libraries(playground_test Catch playground)

enable_testing()
add_test(NAME playground_test COMMAND playground_test)
