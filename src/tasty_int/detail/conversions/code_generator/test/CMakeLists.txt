include(add_google_test)

find_package(GTest REQUIRED)


add_library(
    ${CURRENT_NAMESPACE}table_generator_test_fixture
    STATIC
    table_generator_test_fixture.cpp
    table_generator_test_fixture.hpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}table_generator>
)
target_link_libraries(
    ${CURRENT_NAMESPACE}table_generator_test_fixture
    GTest::GTest
)

add_google_test(
    NAME
    ${CURRENT_NAMESPACE}table_generator_test
    SOURCES
    table_generator_test.cpp
    LIBRARIES
    ${CURRENT_NAMESPACE}table_generator_test_fixture
)

add_google_test(
    NAME
    ${CURRENT_NAMESPACE}token_table_generator_test
    SOURCES
    token_table_generator_test.cpp
    LIBRARIES
    ${CURRENT_NAMESPACE}token_table_generator
    ${CURRENT_NAMESPACE}table_generator_test_fixture
)

add_google_test(
    NAME
    ${CURRENT_NAMESPACE}parse_code_generator_arguments_test
    SOURCES
    parse_code_generator_arguments_test.cpp
    $<TARGET_OBJECTS:${CURRENT_NAMESPACE}parse_code_generator_arguments>
)
