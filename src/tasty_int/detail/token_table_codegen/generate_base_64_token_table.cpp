/**
 * @file generate_base_64_token_table.cpp
 * This program generates the source code for a base-64 tasty_int::detail::TokenTable.
 */
#include "tasty_int/detail/token_table_codegen/generate_token_table.hpp"


using namespace tasty_int::detail::token_table_codegen;

int
main(int   argc,
     char *argv[])
{
    TokenTableGenerator::TokenMap base_64_token_map;

    for (char token = 'A'; token <= 'Z'; ++token)
        base_64_token_map.map_token(token, token - 'A');

    for (char token = 'a'; token <= 'z'; ++token)
        base_64_token_map.map_token(token, token - 'a' + 26);

    for (char token = '0'; token <= '9'; ++token)
        base_64_token_map.map_token(token, token - '0' + 52);

    base_64_token_map.map_token('+', 62);
    base_64_token_map.map_token('/', 63);

    return generate_token_table(argc, argv, base_64_token_map);
}
