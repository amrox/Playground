add_cmocka_test(test_playground
    SOURCES test_library.c
    LINK_LIBRARIES playground cmocka)
    # TODO: I feel like this should link cmocka automatically, figure out why not