cmake_minimum_required(VERSION 3.15)
project(playground C)

set(CMAKE_C_STANDARD 11)

add_library(playground library.c library.h)

add_subdirectory(3rdparty/cmocka-1.1.5)
add_executable(playground-test library-test.c)
target_link_libraries(playground-test PRIVATE playground cmocka)