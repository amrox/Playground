add_library(playground library.c library.h)
target_include_directories(playground 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})