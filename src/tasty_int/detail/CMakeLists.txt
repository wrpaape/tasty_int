set(TASTY_INT_DETAIL_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(token_table_codegen)

foreach(base 36 64)
    add_library(
        tasty_int-detail-value_from_base_${base}_token
        STATIC
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
        $<TARGET_OBJECTS:tasty_int-detail-codegen-base_${base}_token_values>
    )
endforeach()

add_library(
    tasty_int-detail-digits_from_integral
    OBJECT
    digits_from_integral.cpp
    digits_from_integral.hpp
    ${TASTY_INT_DETAIL_INCLUDE_DIR}/digit_type.hpp
)

foreach(kind signed unsigned)
    add_library(
        tasty_int-detail-int_from_${kind}_integral
        STATIC
        int_from_${kind}_integral.cpp
        int_from_${kind}_integral.hpp
        ${TASTY_INT_DETAIL_INCLUDE_DIR}/int.hpp
        ${TASTY_INT_DETAIL_DIR}/sign_from_${kind}_arithmetic.hpp
        $<TARGET_OBJECTS:tasty_int-detail-digits_from_integral>
    )
endforeach()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
