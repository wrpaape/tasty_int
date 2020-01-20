add_google_test(
    NAME
    token_table_generator_test
    SOURCES
    token_table_generator_test.cpp
    $<TARGET_OBJECTS:tasty_int-detail-token_table_codegen-token_table_generator>
)
