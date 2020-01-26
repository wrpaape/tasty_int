#ifndef TASTY_INT_TASTY_INT_TEST_ARITHMETIC_TYPES_HPP
#define TASTY_INT_TASTY_INT_TEST_ARITHMETIC_TYPES_HPP

#include "gtest/gtest.h"


namespace tasty_int_test {

/**
 * The list of supported arithmetic types (taken from
 * https://en.cppreference.com/w/cpp/types/is_integral and
 * https://en.cppreference.com/w/cpp/types/is_floating_point).
 */
using ArithmeticTypes = ::testing::Types<
    // sign-less integral types
    bool,

    // fixed-size char types
#if HAVE_CHAR8_T
    char8_t,
#endif
    char16_t, char32_t, wchar_t,

    // signed integral types
    signed char, signed short int, signed int, signed long int,
    signed long long int,

    // unsigned integral types
    unsigned char, unsigned short int, unsigned int, unsigned long int,
    unsigned long long int,

    // floating point types
    float, double, long double
>;

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_ARITHMETIC_TYPES_HPP
