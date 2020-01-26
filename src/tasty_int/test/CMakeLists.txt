include(add_google_test)

add_google_test(
    NAME      tasty_int_constructors_test
    SOURCES   tasty_int_constructors_test.cpp
              ${TASTY_INT_HEADERS}
    LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
              tasty_int_test
)
