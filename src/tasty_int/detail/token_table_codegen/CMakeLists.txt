add_library(
    tasty_int-detail-token_table_codegen-token_table_generator
    OBJECT
    token_table_generator.cpp
    token_table_generator.hpp
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
