#include "tasty_int/tasty_int.hpp" // TastyInt::*
#include <stdexcept>               // std::invalid_argument


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

    digits_from_string(reinterpret_cast<const unsigned char *>(string),
                       length,
                       base,
                       token_values);

    this->sign = ((digits.size() == 1) && (digits[0] == 0)) ? 0 : sign;
}

void
TastyInt::digits_from_bytes(const unsigned char *begin,
                            const std::size_t length,
                            const unsigned int base)
{
    unsigned char *token = begin + length;
}


