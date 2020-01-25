#ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP
#define TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range_values.hpp"


namespace tasty_int_test {

/**
 * @brief Yields a googletest parameter generator which provides an ascending
 *     sequence of unique values:
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
auto
logarithmic_range(T min, T max, T step)
    requires std::is_arithmetic_v<T>
{
    return ::testing::ValuesIn(logarithmic_range_values(min, max, step));
}

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP
