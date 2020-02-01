#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"

#include <limits>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/unsigned_arithmetic_types.hpp"


namespace {

using tasty_int::detail::Sign;
using tasty_int::detail::sign_from_unsigned_arithmetic;


template<typename UnsignedArithmeticType>
    requires std::is_unsigned_v<UnsignedArithmeticType>
class SignFromUnsignedArithmeticTest : public ::testing::Test
{
protected:
    static constexpr UnsignedArithmeticType min_positive_value()
    {
        return UnsignedArithmeticType(1);
    }

    static constexpr UnsignedArithmeticType max_value()
    {
        return std::numeric_limits<UnsignedArithmeticType>::max();
    }

    static constexpr UnsignedArithmeticType median_value()
    {
        if constexpr (min_positive_value() == max_value()) {
            return min_positive_value();
        } else {
            return (max_value() - min_positive_value())
                 / UnsignedArithmeticType(2);
        }
    }
}; // class SignFromUnsignedArithmeticTest

TYPED_TEST_SUITE(SignFromUnsignedArithmeticTest,
                 tasty_int_test::UnsignedArithmeticTypes);

TYPED_TEST(SignFromUnsignedArithmeticTest, ZeroProducesZeroSign)
{
    TypeParam zero(0);

    EXPECT_EQ(Sign::ZERO,
              sign_from_unsigned_arithmetic(zero));
}

TYPED_TEST(SignFromUnsignedArithmeticTest, MinPositiveValueProducesPositiveSign)
{
    auto min_positive_value = TestFixture::min_positive_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_unsigned_arithmetic(min_positive_value));
}

TYPED_TEST(SignFromUnsignedArithmeticTest, MedianPositiveValueProducesPositiveSign)
{
    auto median_value = TestFixture::median_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_unsigned_arithmetic(median_value));
}

TYPED_TEST(SignFromUnsignedArithmeticTest, MaxPositiveValueProducesPositiveSign)
{
    auto max_value = TestFixture::max_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_unsigned_arithmetic(max_value));
}

} // namespace
