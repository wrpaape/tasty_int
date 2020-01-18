include(add_google_test)

foreach(test_name constructors)
    add_google_test(
        NAME      test_tasty_int_${test_name}
        SOURCES   test_tasty_int_${test_name}.cpp
                  ${TASTY_INT_HEADERS}
        LIBRARIES ${TASTY_INT_SHARED_LIBRARY}
    )
endforeach()
