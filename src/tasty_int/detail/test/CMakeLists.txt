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
    tasty_int-detail-int_from_integral_test_common
    OBJECT
    int_from_integral_test_common.cpp
    int_from_integral_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
)
target_link_libraries(
    tasty_int-detail-int_from_integral_test_common
    GTest::GTest
)
foreach(kind signed unsigned)
    add_google_test(
        NAME      tasty_int-detail-int_from_${kind}_integral_test
        SOURCES   int_from_${kind}_integral_test.cpp
                  $<TARGET_OBJECTS:tasty_int-detail-int_from_integral_test_common>
        LIBRARIES tasty_int-detail-int_from_${kind}_integral
                  tasty_int_test
    )
endforeach()

add_library(
    tasty_int-detail-from_floating_point_test_common
    OBJECT
    from_floating_point_test_common.cpp
    from_floating_point_test_common.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-from_floating_point_test_common
    GTest::GTest
)
add_google_test(
    NAME      tasty_int-detail-digits_from_floating_point_test
    SOURCES   digits_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-digits_from_floating_point>
              $<TARGET_OBJECTS:tasty_int-detail-from_floating_point_test_common>
    LIBRARIES tasty_int_test
)

add_google_test(
    NAME      tasty_int-detail-int_from_floating_point_test
    SOURCES   int_from_floating_point_test.cpp
              $<TARGET_OBJECTS:tasty_int-detail-from_floating_point_test_common>
    LIBRARIES tasty_int-detail-int_from_floating_point
              tasty_int_test
)
