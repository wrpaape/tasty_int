#include "tasty_int/tasty_int.hpp" // TastyInt::*
#include <stdexcept>               // std::invalid_argument
#include <memory>                  // std::[unique_ptr|make_unique]
#include <vector>                  // std::vector


#ifndef CPP_RESTRICT_QUALIFIER
#   warn CPP_RESTRICT_QUALIFIER not defined, ignoring
#   define CPP_RESTRICT_QUALIFIER
#endif // ifndef CPP_RESTRICT_QUALIFIER


// static data
// -----------------------------------------------------------------------------
unsigned int TastyInt::global_default_base = 10;


// helper functions
// -----------------------------------------------------------------------------
namespace {

[[ noreturn ]] inline void
throw_from_string_no_valid_digits()
{
    throw std::invalid_argument(
        "TastyInt::TastyInt(string) -- no valid digits"
    );
}

[[ noreturn ]] inline void
throw_from_string_invalid_digits()
{
    throw std::invalid_argument(
        "TastyInt::TastyInt(string) -- invalid digit(s)"
    );
}

[[ noreturn ]] inline void
throw_from_string_max_base_exceeded()
{
    throw std::invalid_argument(
        "TastyInt::TastyInt(string) -- "
        "input 'base' exceeds TastyInt::max_base (64)"
    );
}

// string of ASCII tokens    (1 -> length, most sig -> least sig) to
// byte-wise array of values (1 -> length, least sig -> most sig)
std::vector<unsigned char> 
bytes_from_string(const unsigned char *const CPP_RESTRICT_QUALIFIER string,
                  const std::size_t length,
                  const char *token_values)
{
    int value;
    const unsigned char *CPP_RESTRICT_QUALIFIER token = string;
    const unsigned char *const CPP_RESTRICT_QUALIFIER
    string_end = &string[length];

    // skip leading zeros
    while (true) {
        value = (int) token_values[*token];

        if (value > 0)
            break;

        if (value < 0)
            throw_from_string_invalid_digits();

        if (++token == string_end)
            throw_from_string_no_valid_digits();
    }

    const unsigned char *const CPP_RESTRICT_QUALIFIER values_begin = token;


    std::unique_ptr<unsigned char[]>
    bytes = std::make_unique<unsigned char[]>(length);

    unsigned char *CPP_RESTRICT_QUALIFIER byte        = bytes.get();
    const unsigned char *CPP_RESTRICT_QUALIFIER token = &string[length];

    do {
        value = (int) token_values[*--token];

        if (value < 0)
            throw_from_string_invalid_digits();

        *byte++ = (unsigned char) value;
    } while (token != string);

    return bytes;
}

} // namespace


// instance methods
// -----------------------------------------------------------------------------
TastyInt::TastyInt(const char *string,
                   std::size_t length,
                   const unsigned int base)
{
    const char *token_values;
    int sign;

    if (base <= 36u)
        token_values = &base_36_token_values[0];
    else if (base <= max_base)
        token_values = &base_64_token_values[0];
    else
        throw_from_string_max_base_exceeded();

    if (length == 0)
        throw_from_string_no_valid_digits();

    if (*string == '-') {
        if (--length == 0)
            throw_from_string_no_valid_digits();

        ++string;
        sign = -1;

    } else {
        sign = 1;
    }


    std::unique_ptr<unsigned char[]> bytes = ::bytes_from_string(
        reinterpret_cast<const unsigned char *>(string),
        length,
        token_values
    );

    // digits_from_string(
    //                    length,
    //                    base,
    //                    token_values);

    this->sign = ((digits.size() == 1) && (digits[0] == 0)) ? 0 : sign;
}

// void
// TastyInt::digits_from_bytes(const unsigned char *begin,
//                             const std::size_t length,
//                             const unsigned int base)
// {
//     unsigned char *token = begin + length;
// }


