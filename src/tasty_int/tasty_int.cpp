#include "tasty_int/tasty_int.hpp" // TastyInt::*
#include <stdexcept>               // std::invalid_argument
#include <memory>                  // std::[unique_ptr|make_unique]
#include <vector>                  // std::vector
#include <string>                  // std::to_string


#ifndef CPP_RESTRICT_QUALIFIER
#   warn CPP_RESTRICT_QUALIFIER not defined, ignoring
#   define CPP_RESTRICT_QUALIFIER
#endif // ifndef CPP_RESTRICT_QUALIFIER


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
        "input 'base' exceeds TastyInt::MAX_BASE "
        "(" + std::to_string(TastyInt::MAX_BASE) + ')'
    );
}

// string of ASCII tokens    (1 -> length, most sig -> least sig) to
// byte-wise array of values (1 -> length, least sig -> most sig)

namespace base_power_of_two {

std::size_t
write_bytes(unsigned char *CPP_RESTRICT_QUALIFIER digit,
            const unsigned char *const CPP_RESTRICT_QUALIFIER string_begin,
            const unsigned char *const CPP_RESTRICT_QUALIFIER string_end,
            const char *token_values,
            const unsigned int base_bit)
{
    return 0; // TODO: get compiling
}

} // namespace base_power_of_two

void digits_from_string(const unsigned char *string_begin,
                        const std::size_t length,
                        const unsigned int base,
                        const char *token_values)
{
#if 0 // TODO
    int value;
    const unsigned char *CPP_RESTRICT_QUALIFIER token = string_begin;
    const unsigned char *const CPP_RESTRICT_QUALIFIER
    string_end = &string_begin[length];

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
    const unsigned char *CPP_RESTRICT_QUALIFIER token = &string_begin[length];

    do {
        value = (int) token_values[*--token];

        if (value < 0)
            throw_from_string_invalid_digits();

        *byte++ = (unsigned char) value;
    } while (token != string_begin);

    return bytes;
#endif
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
        token_values = &BASE_36_TOKEN_VALUES[0];
    else if (base <= MAX_BASE)
        token_values = &BASE_64_TOKEN_VALUES[0];
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


