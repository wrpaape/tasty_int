include(add_google_test)
include(set_have_type)

set_have_type(char8_t)
add_definitions(-DHAVE_CHAR8_T=${HAVE_CHAR8_T})

foreach(test_name constructors)
    add_google_test(
        NAME      tasty_int_${test_name}_test
        SOURCES   tasty_int_${test_name}_test.cpp
                  ${TASTY_INT_HEADERS}
        LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
    )
endforeach()
