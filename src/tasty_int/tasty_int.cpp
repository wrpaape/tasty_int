#include "tasty_int/tasty_int.hpp"


// static data
// -----------------------------------------------------------------------------
unsigned int TastyInt::global_default_base = 10;


// instance methods
// -----------------------------------------------------------------------------
void
TastyInt::digits_from_bytes(const unsigned char *begin,
                            const std::size_t length,
                            const unsigned int base)
{
    unsigned char *token = begin + length;
}
