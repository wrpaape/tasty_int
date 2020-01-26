#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/signed_arithmetic_types.hpp"


using namespace tasty_int::detail;

namespace {

template<typename SignedArithmeticType>
class SignFromSignedArithmeticTest : public ::testing::Test
{
protected:
    static constexpr SignedArithmeticType min_negative_value()
    {
        return std::numeric_limits<SignedArithmeticType>::lowest();
    }

    static constexpr SignedArithmeticType max_negative_value()
    {
        if constexpr (std::is_integral_v<SignedArithmeticType>) {
            return SignedArithmeticType(-1);
        } else {
            return -std::numeric_limits<SignedArithmeticType>::epsilon();
        }
    }

    static constexpr SignedArithmeticType median_negative_value()
    {
        return (min_negative_value() - max_negative_value())
             / SignedArithmeticType(2);
    }

    static constexpr SignedArithmeticType min_positive_value()
    {
        return -max_negative_value();
    }

    static constexpr SignedArithmeticType max_positive_value()
    {
        return std::numeric_limits<SignedArithmeticType>::max();
    }

    static constexpr SignedArithmeticType median_positive_value()
    {
        return (max_positive_value() - min_positive_value())
             / SignedArithmeticType(2);
    }
}; // class SignFromSignedArithmeticTest

TYPED_TEST_SUITE(SignFromSignedArithmeticTest,
                 tasty_int_test::SignedArithmeticTypes);

TYPED_TEST(SignFromSignedArithmeticTest, MinNegativeValueProducesNegativeSign)
{
    auto min_negative_value = TestFixture::min_negative_value();

    EXPECT_EQ(Sign::NEGATIVE,
              sign_from_signed_arithmetic(min_negative_value));
}

TYPED_TEST(SignFromSignedArithmeticTest, MedianNegativeValueProducesNegativeSign)
{
    auto median_negative_value = TestFixture::median_negative_value();

    EXPECT_EQ(Sign::NEGATIVE,
              sign_from_signed_arithmetic(median_negative_value));
}

TYPED_TEST(SignFromSignedArithmeticTest, MaxNegativeValueProducesNegativeSign)
{
    auto max_negative_value = TestFixture::max_negative_value();

    EXPECT_EQ(Sign::NEGATIVE,
              sign_from_signed_arithmetic(max_negative_value));
}

TYPED_TEST(SignFromSignedArithmeticTest, ZeroProducesZeroSign)
{
    TypeParam zero(0);

    EXPECT_EQ(Sign::ZERO,
              sign_from_signed_arithmetic(zero));
}

TYPED_TEST(SignFromSignedArithmeticTest, MinPositiveValueProducesPositiveSign)
{
    auto min_positive_value = TestFixture::min_positive_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_signed_arithmetic(min_positive_value));
}

TYPED_TEST(SignFromSignedArithmeticTest, MedianPositiveValueProducesPositiveSign)
{
    auto median_positive_value = TestFixture::median_positive_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_signed_arithmetic(median_positive_value));
}

TYPED_TEST(SignFromSignedArithmeticTest, MaxPositiveValueProducesPositiveSign)
{
    auto max_positive_value = TestFixture::max_positive_value();

    EXPECT_EQ(Sign::POSITIVE,
              sign_from_signed_arithmetic(max_positive_value));
}

} // namespace
