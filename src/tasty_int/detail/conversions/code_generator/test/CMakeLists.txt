include(add_google_test)

find_package(GTest REQUIRED)


add_library(
    tasty_int-detail-conversions-code_generator-table_generator_test_fixture
    STATIC
    table_generator_test_fixture.cpp
    table_generator_test_fixture.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-table_generator>
)
target_link_libraries(
    tasty_int-detail-conversions-code_generator-table_generator_test_fixture
    GTest::GTest
)

add_google_test(
    NAME
    tasty_int-detail-conversions-code_generator-table_generator_test
    SOURCES
    table_generator_test.cpp
    LIBRARIES
    tasty_int-detail-conversions-code_generator-table_generator_test_fixture
)

add_google_test(
    NAME
    tasty_int-detail-conversions-code_generator-token_table_generator_test
    SOURCES
    token_table_generator_test.cpp
    LIBRARIES
    tasty_int-detail-conversions-code_generator-token_table_generator
    tasty_int-detail-conversions-code_generator-table_generator_test_fixture
)

add_google_test(
    NAME
    tasty_int-detail-conversions-code_generator-parse_code_generator_arguments_test
    SOURCES
    parse_code_generator_arguments_test.cpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-parse_code_generator_arguments>
)
