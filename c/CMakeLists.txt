cmake_minimum_required(VERSION 3.15)
project(playground C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(src)

option(ENABLE_TESTS "Perform unit tests after build" OFF)
if (ENABLE_TESTS)

    # cmocka
    set(CMOCKA_DIR "${CMAKE_SOURCE_DIR}/3rdparty/cmocka-1.1.5")
    add_subdirectory("${CMOCKA_DIR}")
    list(APPEND CMAKE_MODULE_PATH "${CMOCKA_DIR}/cmake/Modules")
    
    include(AddCMockaTest)
    add_subdirectory(test)
    enable_testing()

endif(ENABLE_TESTS)