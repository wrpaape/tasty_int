#ifndef TASTY_INT_TASTY_INT_TEST_UNSIGNED_ARITHMETIC_TYPES_HPP
#define TASTY_INT_TASTY_INT_TEST_UNSIGNED_ARITHMETIC_TYPES_HPP

#include <type_traits>

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/detail/filter_types.hpp"


namespace tasty_int_test {

using UnsignedArithmeticTypes =
    detail::FilterTypes<ArithmeticTypes, std::is_unsigned>;

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_UNSIGNED_ARITHMETIC_TYPES_HPP
