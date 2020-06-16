#include "tasty_int/detail/test/integer_arithmetic_test_common.hpp"

#include <cmath>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/signed_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"
#include "tasty_int_test/expect_approx.hpp"


namespace integer_arithmetic_test_common {

using tasty_int::detail::conversions::unsigned_integral_from_integer;
using tasty_int::detail::conversions::signed_integral_from_integer;
using tasty_int::detail::conversions::floating_point_from_integer;


void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              const tasty_int::detail::Integer &result)
{
    EXPECT_EQ(expected_result, result);
}

void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              std::uintmax_t                    result)
{
    EXPECT_EQ(unsigned_integral_from_integer(expected_result), result);
}

void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              std::intmax_t                     result)
{
    EXPECT_EQ(signed_integral_from_integer(expected_result), result);
}

void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              long double                       result)
{
    EXPECT_APPROX(floating_point_from_integer(expected_result),
                  std::trunc(result));
}

} // namespace integer_arithmetic_test_common
