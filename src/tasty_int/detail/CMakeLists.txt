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
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
