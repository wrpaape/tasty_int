include(add_google_test)

add_google_test(
    NAME      tasty_int
    SOURCES   test_tasty_int.cpp
              ${TASTY_INT_INCLUDE_DIR}/cmake_tutorial.hpp
    LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
)
