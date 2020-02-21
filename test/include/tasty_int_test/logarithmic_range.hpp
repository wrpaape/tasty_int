#ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP
#define TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range_values.hpp"


namespace tasty_int_test {

/**
 * @brief Yields the following sequence of unique values:
 *
 *     { first [, first +/- scale [, first +/- scale^2] ...] [, last] }
 *
 * @detail If `first < last`, the sequence is ascending.  If `first > last`,
 *     the sequence is descending.  Otherwise, if `first == last`, the single
 *     value @p first is returned.
 *
 * @param[in] first the first value of the range (inclusive)
 * @param[in] last  the last value of the range (inclusive)
 * @param[in] scale the logarithmic scale of the range
 * @return the specified logarithmic sequence of values as a google test
 *     parameter generator
 *
 * @pre `scale > 1`
 *
 * @throw std::invalid_argument if `scale <= 1`
 */
template<typename T>
auto
logarithmic_range(T first, T last, T scale)
    requires std::is_arithmetic_v<T>
{
    return ::testing::ValuesIn(logarithmic_range_values(first, last, scale));
}

} //  namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_LOGARITHMIC_RANGE_HPP
