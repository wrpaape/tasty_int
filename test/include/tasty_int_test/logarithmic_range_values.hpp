#ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP
#define TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP

#include <cmath>

#include <vector>
#include <type_traits>
#include <stdexcept>
#include <sstream>

#include "tasty_int_test/make_arithmetic_printable.hpp"


namespace tasty_int_test {
namespace detail {

template<typename T>
void
check_logarithmic_scale(T scale)
    requires std::is_arithmetic_v<T>
{
    if (scale <= 1) {
        std::ostringstream error_message;
        error_message <<
            "tasty_int_test::logarithmic_range_values - scale ("
            << make_arithmetic_printable(scale) << ") <= 1.";

        throw std::invalid_argument(error_message.str());
    }
}

template<typename T>
void
append_intermediate_logarithmic_values(T first, T scale, T last_mult,
                                       std::vector<T>& values)
    requires std::is_arithmetic_v<T>
          && std::is_signed_v<T>
{
    for (T mult = static_cast<T>(std::copysign(scale, last_mult));
         std::abs(mult) <= std::abs(last_mult); mult *= scale)
        values.emplace_back(first + mult);
}

template<typename T>
void
append_intermediate_logarithmic_values(T first, T scale, T last_mult,
                                       std::vector<T>& values)
    requires std::is_arithmetic_v<T>
          && std::is_unsigned_v<T>
{
    for (T mult = scale; mult <= last_mult; mult *= scale)
        values.emplace_back(first + mult);
}

} // namespace detail


/**
 * @brief Yields the following sequence of unique values:
 *
 *     { first [, first +/- scale [, first +/- scale^2] ...] [, last] }
 *
 * @details If `first < last`, the sequence is ascending.  If `first > last`,
 *     the sequence is descending.  Otherwise, if `first == last`, the single
 *     value @p first is returned.
 *
 * @param[in] first the first value of the range (inclusive)
 * @param[in] last  the last value of the range (inclusive)
 * @param[in] scale the logarithmic scale of the range
 * @return the specified logarithmic sequence of values
 *
 * @pre `scale > 1`
 *
 * @throw std::invalid_argument if `scale <= 1`
 */
template<typename T>
std::vector<T>
logarithmic_range_values(T first, T last, T scale)
    requires std::is_arithmetic_v<T>
{
    detail::check_logarithmic_scale(scale);

    std::vector<T> values;
    T last_mult = (last - first) / scale;

    values.emplace_back(first);

    detail::append_intermediate_logarithmic_values(first, scale, last_mult,
                                                   values);

    if (last != first)
        values.emplace_back(last);

    return values;
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_VALUES_HPP
