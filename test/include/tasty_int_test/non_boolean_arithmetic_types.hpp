#ifndef TASTY_INT_TASTY_INT_TEST_NON_BOOLEAN_ARITHMETIC_TYPES_HPP
#define TASTY_INT_TASTY_INT_TEST_NON_BOOLEAN_ARITHMETIC_TYPES_HPP

#include <type_traits>

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/detail/filter_types.hpp"


namespace tasty_int_test {
namespace detail {

template<typename T>
struct IsNonBoolean
{
    static constexpr bool value = !std::is_same_v<T, bool>;
}; // struct IsNonBoolean

} // namespace detail


using NonBooleanArithmeticTypes =
    detail::FilterTypes<ArithmeticTypes, detail::IsNonBoolean>;

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_NON_BOOLEAN_ARITHMETIC_TYPES_HPP
