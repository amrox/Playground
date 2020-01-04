set(LINK_LIBRARIES playground cmocka)

add_cmocka_test(test_playground
    SOURCES test_library.c
    LINK_LIBRARIES ${LINK_LIBRARIES})