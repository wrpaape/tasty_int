/**
 * @file generate_base_36_token_table.cpp
 * This program generates the source code for a base-36 tasty_int::detail::TokenTable.
 */
#include "tasty_int/detail/code_generator/generate_token_table.hpp"


int
main(int   argc,
     char *argv[])
{
    using tasty_int::detail::code_generator::TokenTableGenerator;
    using tasty_int::detail::code_generator::generate_token_table;

    TokenTableGenerator::TokenMap base_36_token_map;

    for (char token = '0'; token <= '9'; ++token)
        base_36_token_map.map_token(token, token & ~'0');

    for (char token = 'A'; token <= 'Z'; ++token)
        base_36_token_map.map_token(token, token - 'A' + 10);

    for (char token = 'a'; token <= 'z'; ++token)
        base_36_token_map.map_token(token, token - 'a' + 10);

    return generate_token_table(argc, argv, base_36_token_map);
}
