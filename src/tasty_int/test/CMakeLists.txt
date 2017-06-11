include(add_google_test)
include(add_unity_test)
include(add_catch_test)

foreach(test_name constructors)
    add_google_test(
        NAME      test_tasty_int_${test_name}
        SOURCES   test_tasty_int_${test_name}.cpp
                  ${TASTY_INT_HEADERS}
        LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
    )

add_unity_test(
    NAME    test_unity_test
    SOURCES test_unity_test.c
)
add_catch_test(
    NAME    test_catch_test
    SOURCES test_catch_test.cpp
)
endforeach()
