include(add_google_test)

find_package(GTest REQUIRED)

foreach(base 36 64)
    add_google_test(
        NAME      tasty_int-detail-value_from_base_${base}_token_test
        SOURCES   value_from_base_${base}_token_test.cpp
        LIBRARIES tasty_int-detail-value_from_base_${base}_token
    )
endforeach()

foreach(kind signed unsigned)
    add_google_test(
        NAME    tasty_int-detail-sign_from_${kind}_arithmetic_test
        SOURCES sign_from_${kind}_arithmetic_test.cpp
                ${TASTY_INT_DETAIL_DIR}/sign_from_${kind}_arithmetic.hpp
    )
endforeach()

add_google_test(
    NAME    tasty_int-detail-digit_type_test
    SOURCES digit_type_test.cpp
)

add_google_test(
    NAME      tasty_int-detail-digits_from_integral_test
    SOURCES   digits_from_integral_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_from_integral>
    LIBRARIES tasty_int_test
)

add_library(
    tasty_int-detail-int_from_integral_test
    OBJECT
    int_from_integral_test.cpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
)
target_link_libraries(
    tasty_int-detail-int_from_integral_test
    GTest::GTest
)
foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-int_from_${kind}_integral_test
        SOURCES   int_from_${kind}_integral_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-int_from_integral_test>
        LIBRARIES tasty_int-detail-int_from_${kind}_integral
                  tasty_int_test
    )
endforeach()
