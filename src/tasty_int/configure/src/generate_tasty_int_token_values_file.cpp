#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <unordered_map>



class TokenMap : public std::unordered_map<unsigned char, unsigned int>
{
public:
    using std::unordered_map<unsigned char, unsigned int>::unordered_map;

    TokenMap::mapped_type
    get(const TokenMap::key_type &token) const
    {
        TokenMap::const_iterator found = find(token);

        return (found == end()) ? default_value : found->second;
    }

private:
    static const TokenMap::mapped_type default_value = 0;
};


class Generator
{
public:
    Generator(const char *const path)
        : file(path,
               std::ofstream::out | std::ofstream::trunc)
    {
        file << std::setfill(' ');
    }

    void
    put_head()
    {
        std::chrono::time_point<std::chrono::system_clock> time_now;
        std::time_t timestamp;

        time_now  = std::chrono::system_clock::now();
        timestamp = std::chrono::system_clock::to_time_t(time_now);

        file << "// token -> value lookup tables for TastyInt (DO NOT MODIFY)\n"
                "//\n"
                "// generated on: " << std::ctime(&timestamp) << // terminated with \n
                "// =============================================================================\n"
                "#include \"tasty_int/tasty_int.hpp\" // TastyInt::*\n";
    }

    template<typename T>
    void
    put(const T &thing)
    {
        file << thing;
    }

    void
    put_map(const char *label,
            const TokenMap &map)
    {
        unsigned int token;
        unsigned int row_end;

        file << "const unsigned char TastyInt::"
             << label << "_token_values[" << token_count << "] = {\n";

        token = 0;
         do {
            row_end = token + row_count;
            if (row_end > token_count)
                row_end = token_count;

            // put values
            file << "    ", put_value(map, token);

            while (++token < row_end)
                file << ", ", put_value(map, token);

            file << ",\n";

            token = row_end;
        } while (token < token_count);

        file << "};\n";
    }


private:
    std::ofstream file;

    static const unsigned int
    token_max = std::numeric_limits<TokenMap::key_type>::max();
    static const unsigned int token_count = token_max + 1;
    static const unsigned int row_count   = 19;

    void
    put_value(const TokenMap &map,
              const TokenMap::key_type &token)
    {
        file << std::setw(2) << map.get(token);
    }
}; // class Generator



int
main(int argc,
     char *argv[])
{
    if (argc < 2) {
        std::cerr << "expected 'path' as single argument" << std::endl;
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

    Generator generator(argv[1]);

    generator.put_head();
    generator.put("\n\n\n");
    generator.put_map("base_36", base_36);
    generator.put("\n\n");
    generator.put_map("base_64", base_64);

    return 0;
}
