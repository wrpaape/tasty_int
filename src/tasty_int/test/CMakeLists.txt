include(add_google_test)
include(set_have_type)

set_have_type(char8_t)
add_google_test(
    NAME                tasty_int_constructors_test
    SOURCES             tasty_int_constructors_test.cpp
                        ${TASTY_INT_HEADERS}
    COMPILE_DEFINITIONS -DHAVE_CHAR8_T=${HAVE_CHAR8_T}
    LIBRARIES           ${TASTY_INT_SHARED_LIBRARY}
)
