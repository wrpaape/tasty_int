add_subdirectory(token_table_codegen)

foreach(base 36 64)
    set(value_from_base_token tasty_int-detail-value_from_base_${base}_token)
    add_library(
        ${value_from_base_token}
        OBJECT
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
    )
    target_link_libraries(
        ${value_from_base_token}
        $<TARGET_OBJECTS:tasty_int-detail-codegen-base_${base}_token_values>
    )
endforeach()


if(BUILD_TESTING)
    add_subdirectory(test)
endif()
