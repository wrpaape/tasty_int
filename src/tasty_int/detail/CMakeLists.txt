foreach(base 36 64)
    add_library(
        tasty_int-detail-value_from_base_${base}_token
        OBJECT
        value_from_base_${base}_token.cpp
        value_from_base_${base}_token.hpp
    )
endforeach()

add_subdirectory(token_table_codegen)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
