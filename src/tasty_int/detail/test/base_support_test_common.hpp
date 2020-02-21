#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_BASE_SUPPORT_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_BASE_SUPPORT_TEST_COMMON_HPP

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range_values.hpp"


namespace base_support_test_common {

/**
 * Yields all numeric bases that are supported by tasty_int.
 *
 * @return a google test parameter generator for all supported bases
 */
auto
supported_bases()
{
    return ::testing::Range<unsigned int>(2, 64);
}

/**
 * Yields a sampling of numeric bases that are *not* supported by tasty_int.
 *
 * @return a google test parameter generator for a sampling of unsupported
 *     bases
 */
auto
unsupported_bases()
{
    auto values = tasty_int_test::logarithmic_range_values<unsigned int>(
        65, std::numeric_limits<unsigned int>::max(), 2
    );
    values.emplace_back(0);
    values.emplace_back(1);

    return ::testing::ValuesIn(values);
}

} // namespace base_support_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_BASE_SUPPORT_TEST_COMMON_HPP
