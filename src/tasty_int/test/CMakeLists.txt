include(add_google_test)

add_google_test(
    NAME      tasty_int
    SOURCES   test_tasty_int.cpp
              ${TASTY_INT_HEADERS}
    LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
)
