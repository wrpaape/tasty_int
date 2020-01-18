#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <unordered_map>


namespace {

class TokenMap : public std::unordered_map<unsigned char, int>
{
public:
    using std::unordered_map<unsigned char, int>::unordered_map;

    TokenMap::mapped_type
    get(const TokenMap::key_type &token) const;

private:
    static const TokenMap::mapped_type default_value = -1;
};

TokenMap::mapped_type
TokenMap::get(const TokenMap::key_type &token) const
{
    TokenMap::const_iterator found = find(token);

    return (found == end()) ? default_value : found->second;
}


class Generator
{
public:
    Generator(const char *const output_file_path);

    void
    put_head();

    template<typename T>
    void
    put(const T &thing);

    void
    put_map(const char     *label,
            const TokenMap &map);


private:
    std::ofstream output_file;

    static constexpr unsigned int TOKEN_MAX   =
        std::numeric_limits<TokenMap::key_type>::max();
    static constexpr unsigned int TOKEN_COUNT = TOKEN_MAX + 1;
    static constexpr unsigned int ROW_COUNT   = 19;

    void
    put_value(const TokenMap           &map,
              const TokenMap::key_type &token)
    {
        output_file << std::setw(2) << map.get(token);
    }
}; // class Generator

Generator::Generator(const char *const output_file_path)
    : output_file(output_file_path,
           std::ofstream::out | std::ofstream::trunc)
{
    output_file << std::setfill(' ');
}

void
Generator::put_head()
{
    auto time_now  = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(time_now);

    output_file
        << "// token -> value lookup tables for TastyInt (DO NOT MODIFY)\n"
           "//\n"
           "// generated on: " << std::ctime(&timestamp) // terminated with \n
        << "// =============================================================================\n"
           "#include \"tasty_int/tasty_int.hpp\" // TastyInt::*\n";
}

template<typename T>
void
Generator::put(const T &thing)
{
    output_file << thing;
}

void
Generator::put_map(const char     *label,
                   const TokenMap &map)
{
    output_file << "const TastyInt::TokenMap TastyInt::"
         << label << "_TOKEN_VALUES = {\n";

    unsigned int token = 0;
     do {
        unsigned int row_end = token + ROW_COUNT;
        if (row_end > TOKEN_COUNT)
            row_end = TOKEN_COUNT;

        // put values
        output_file << "    ", put_value(map, token);

        while (++token < row_end)
            output_file << ", ", put_value(map, token);

        output_file << ",\n";

        token = row_end;
    } while (token < TOKEN_COUNT);

    output_file << "};\n";
}


void
print_usage(const char   *program,
            std::ostream &output)
{
    if (!program)
        program = "./generate_tasty_int_token_values_file";

    output << program << " <path to output file>" << std::endl;
}

} // namespace

int
main(int   argc,
     char *argv[])
{
    if (argc < 2) {
        const char *program = argv[0];
        print_usage(program, std::cerr);
        return 1;
    }

    const TokenMap base_36 = {
        { '0',  0 }, { '1',  1 }, { '2',  2 }, { '3',  3 }, { '4',  4 },
        { '5',  5 }, { '6',  6 }, { '7',  7 }, { '8',  8 }, { '9',  9 },

        { 'a', 10 }, { 'b', 11 }, { 'c', 12 }, { 'd', 13 }, { 'e', 14 },
        { 'f', 15 }, { 'g', 16 }, { 'h', 17 }, { 'i', 18 }, { 'j', 19 },
        { 'k', 20 }, { 'l', 21 }, { 'm', 22 }, { 'n', 23 }, { 'o', 24 },
        { 'p', 25 }, { 'q', 26 }, { 'r', 27 }, { 's', 28 }, { 't', 29 },
        { 'u', 30 }, { 'v', 31 }, { 'w', 32 }, { 'x', 33 }, { 'y', 34 },
        { 'z', 35 },

        { 'A', 10 }, { 'B', 11 }, { 'C', 12 }, { 'D', 13 }, { 'E', 14 },
        { 'F', 15 }, { 'G', 16 }, { 'H', 17 }, { 'I', 18 }, { 'J', 19 },
        { 'K', 20 }, { 'L', 21 }, { 'M', 22 }, { 'N', 23 }, { 'O', 24 },
        { 'P', 25 }, { 'Q', 26 }, { 'R', 27 }, { 'S', 28 }, { 'T', 29 },
        { 'U', 30 }, { 'V', 31 }, { 'W', 32 }, { 'X', 33 }, { 'Y', 34 },
        { 'Z', 35 },
    };

    const TokenMap base_64 = {
        { 'A',  0 }, { 'Q', 16 }, { 'g', 32 }, { 'w', 48 },
        { 'B',  1 }, { 'R', 17 }, { 'h', 33 }, { 'x', 49 },
        { 'C',  2 }, { 'S', 18 }, { 'i', 34 }, { 'y', 50 },
        { 'D',  3 }, { 'T', 19 }, { 'j', 35 }, { 'z', 51 },
        { 'E',  4 }, { 'U', 20 }, { 'k', 36 }, { '0', 52 },
        { 'F',  5 }, { 'V', 21 }, { 'l', 37 }, { '1', 53 },
        { 'G',  6 }, { 'W', 22 }, { 'm', 38 }, { '2', 54 },
        { 'H',  7 }, { 'X', 23 }, { 'n', 39 }, { '3', 55 },
        { 'I',  8 }, { 'Y', 24 }, { 'o', 40 }, { '4', 56 },
        { 'J',  9 }, { 'Z', 25 }, { 'p', 41 }, { '5', 57 },
        { 'K', 10 }, { 'a', 26 }, { 'q', 42 }, { '6', 58 },
        { 'L', 11 }, { 'b', 27 }, { 'r', 43 }, { '7', 59 },
        { 'M', 12 }, { 'c', 28 }, { 's', 44 }, { '8', 60 },
        { 'N', 13 }, { 'd', 29 }, { 't', 45 }, { '9', 61 },
        { 'O', 14 }, { 'e', 30 }, { 'u', 46 }, { '+', 62 },
        { 'P', 15 }, { 'f', 31 }, { 'v', 47 }, { '/', 63 },
    };

    const char *output_file_path = argv[1];
    Generator generator(argv[1]);

    generator.put_head();
    generator.put("\n\n\n");
    generator.put_map("BASE_36", base_36);
    generator.put("\n\n");
    generator.put_map("BASE_64", base_64);

    return 0;
}
