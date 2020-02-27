#ifndef TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP
#define TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP

#include <type_traits>


namespace tasty_int_test {

/**
 * @brief Convert @p value to a type that std::ostreams will print numerically.
 *
 * @param[in] value an arithmetic value
 * @return @p value in a type interpretted as numeric by std::ostreams
 */
template<typename T>
auto
make_arithmetic_printable(T value)
    requires std::is_arithmetic_v<T>
{
    return +value; // promote to int if char
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP
