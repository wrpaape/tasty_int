include(add_google_test)

add_google_test(
    NAME
    tasty_int-detail-code_generator-token_table_generator_test
    SOURCES
    token_table_generator_test.cpp
    $<TARGET_OBJECTS:tasty_int-detail-code_generator-token_table_generator>
)
