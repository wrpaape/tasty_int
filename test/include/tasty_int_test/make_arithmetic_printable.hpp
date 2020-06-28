#ifndef TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP
#define TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP

#include <cstdint>

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
    if constexpr (std::is_floating_point_v<T>)
        return static_cast<long double>(value);
    else if constexpr (std::is_signed_v<T>)
        return static_cast<std::intmax_t>(value);
    else
        return static_cast<std::uintmax_t>(value);
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_MAKE_ARITHMETIC_PRINTABLE_HPP
