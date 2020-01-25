#ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP
#define TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP

#include <vector>
#include <type_traits>
#include <stdexcept>
#include <sstream>


namespace tasty_int_test {
namespace detail {

template<typename T>
auto
make_printable(T value)
    requires std::is_arithmetic_v<T>
{
    return +value; // promote to int if char
}

template<typename T>
void
check_logarithmic_range_values_min_max(T min, T max)
    requires std::is_arithmetic_v<T>
{
    if (min > max) {
        std::ostringstream error_message;
        error_message <<
            "tasty_int_test::logarithmic_range_values - min ("
         << make_printable(min) << ") > max (" << make_printable(max) << ").";

        throw std::invalid_argument(error_message.str());
    }
}

template<typename T>
void
check_logarithmic_range_values_step(T step)
    requires std::is_arithmetic_v<T>
{
    if (step <= 1) {
        std::ostringstream error_message;
        error_message <<
            "tasty_int_test::logarithmic_range_values - step ("
            << make_printable(step) << ") <= 1.";

        throw std::invalid_argument(error_message.str());
    }
}

template<typename T>
void
check_logarithmic_range_values_input(T min, T max, T step)
    requires std::is_arithmetic_v<T>
{ 
    check_logarithmic_range_values_min_max(min, max);
    check_logarithmic_range_values_step(step);
}

} // namespace detail

/**
 * @brief Yields ascending sequence of unique values:
 *
 *     { min [, min + step [, min + step^2] ...] [, max] }
 *
 * @param min  the minimum value of the range (inclusive)
 * @param max  the maximum value of the range (inclusive)
 * @param step the logarithmic scale of the range
 *
 * @pre `min <= max && step > 1`
 *
 * @throws std::invalid_argument if preconditions aren't satisfied
 */
template<typename T>
std::vector<T>
logarithmic_range_values(T min, T max, T step)
    requires std::is_arithmetic_v<T>
{
    detail::check_logarithmic_range_values_input(min, max, step);

    std::vector<T> values;
    T max_mult = (max - min) / step;

    values.emplace_back(min);
    for (T mult = step; mult <= max_mult; mult *= step)
        values.emplace_back(min + mult);

    if (max > min)
        values.emplace_back(max);

    return values;
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP
