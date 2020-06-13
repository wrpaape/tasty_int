#include "tasty_int/detail/integer_operation.hpp"

#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int::detail::Sign;
using tasty_int::detail::Integer;
using tasty_int::detail::signs_agree;
using tasty_int::detail::sign_from_integer_operand;
using tasty_int::detail::value_from_integer_operand;
using tasty_int::detail::sign_and_value_from_arithmetic;
using tasty_int::detail::sign_from_signed_arithmetic;
using tasty_int::detail::sign_from_unsigned_arithmetic;


class SignsAgreeTest : public ::testing::TestWithParam<std::pair<Sign, Sign>>
{}; // class SignsAgreeTest

TEST_P(SignsAgreeTest, SignsAgree)
{
    Sign sign1 = GetParam().first;
    Sign sign2 = GetParam().second;

    EXPECT_TRUE(signs_agree(sign1, sign2));
    EXPECT_TRUE(signs_agree(sign2, sign1));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    SignsAgreeTest,
    ::testing::ValuesIn(
        std::vector<std::pair<Sign, Sign>> {
            { Sign::POSITIVE, Sign::POSITIVE },
            { Sign::POSITIVE, Sign::ZERO     },
            { Sign::NEGATIVE, Sign::NEGATIVE },
            { Sign::NEGATIVE, Sign::ZERO     },
            { Sign::ZERO,     Sign::ZERO     }
        }
    )
);

TEST(SignsDisagreeTest, SignsDisagree)
{
    EXPECT_FALSE(signs_agree(Sign::POSITIVE, Sign::NEGATIVE));
    EXPECT_FALSE(signs_agree(Sign::NEGATIVE, Sign::POSITIVE));
}


class LargerOfAgreeingSignsTest
    : public ::testing::TestWithParam<std::tuple<Sign, Sign, Sign>>
{}; // class LargerOfAgreeingSignsTest

TEST_P(LargerOfAgreeingSignsTest, ProducesExpectedLargerSign)
{
    Sign sign1                = std::get<0>(GetParam());
    Sign sign2                = std::get<1>(GetParam());
    Sign expected_larger_sign = std::get<2>(GetParam());

    EXPECT_EQ(expected_larger_sign, larger_of_agreeing_signs(sign1, sign2));
    EXPECT_EQ(expected_larger_sign, larger_of_agreeing_signs(sign2, sign1));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    LargerOfAgreeingSignsTest,
    ::testing::ValuesIn(
        std::vector<std::tuple<Sign, Sign, Sign>> {
            { Sign::POSITIVE, Sign::POSITIVE, Sign::POSITIVE },
            { Sign::POSITIVE, Sign::ZERO,     Sign::POSITIVE },
            { Sign::NEGATIVE, Sign::NEGATIVE, Sign::NEGATIVE },
            { Sign::NEGATIVE, Sign::ZERO,     Sign::NEGATIVE },
            { Sign::ZERO,     Sign::ZERO,     Sign::ZERO     }
        }
    )
);


class IntegerOperandIntegerTest : public ::testing::TestWithParam<Integer>
{}; // class IntegerOperandIntegerTest

TEST_P(IntegerOperandIntegerTest, SignFromIntegerOperand)
{
    auto integer = GetParam();

    EXPECT_EQ(integer.sign, sign_from_integer_operand(integer));
}

TEST_P(IntegerOperandIntegerTest, ValueFromIntegerOperand)
{
    auto integer = GetParam();

    EXPECT_EQ(integer.digits, value_from_integer_operand(integer));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    IntegerOperandIntegerTest,
    ::testing::ValuesIn(
        std::vector<Integer> {
            { .sign = Sign::POSITIVE, .digits = { 1 } },
            { .sign = Sign::NEGATIVE, .digits = { 2 } },
            { .sign = Sign::ZERO,     .digits = { 0 } }
        }
    )
);


class IntegerOperandUnsignedIntegralTest
    : public ::testing::TestWithParam<std::uintmax_t>
{}; // class IntegerOperandUnsignedIntegralTest

TEST_P(IntegerOperandUnsignedIntegralTest, SignFromIntegerOperand)
{
    auto unsigned_integral = GetParam();

    EXPECT_EQ(sign_from_unsigned_arithmetic(unsigned_integral),
              sign_from_integer_operand(unsigned_integral));
}

TEST_P(IntegerOperandUnsignedIntegralTest, ValueFromIntegerOperand)
{
    auto unsigned_integral = GetParam();

    EXPECT_EQ(unsigned_integral, value_from_integer_operand(unsigned_integral));
}

TEST_P(IntegerOperandUnsignedIntegralTest, SignAndValueFromArithmetic)
{
    auto unsigned_integral       = GetParam();
    auto expected_sign_and_value = std::make_pair(
        sign_from_unsigned_arithmetic(unsigned_integral),
        unsigned_integral
    );

    EXPECT_EQ(expected_sign_and_value,
              sign_and_value_from_arithmetic(unsigned_integral));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    IntegerOperandUnsignedIntegralTest,
    ::testing::ValuesIn(
        tasty_int_test::SampleArithmetic<std::uintmax_t>::VALUES
    )
);

class IntegerOperandSignedIntegralTest
    : public ::testing::TestWithParam<std::intmax_t>
{}; // class IntegerOperandSignedIntegralTest

TEST_P(IntegerOperandSignedIntegralTest, SignFromIntegerOperand)
{
    auto signed_integral = GetParam();

    EXPECT_EQ(sign_from_signed_arithmetic(signed_integral),
              sign_from_integer_operand(signed_integral));
}

TEST_P(IntegerOperandSignedIntegralTest, ValueFromIntegerOperand)
{
    auto signed_integral = GetParam();

    EXPECT_EQ(static_cast<std::uintmax_t>(std::abs(signed_integral)),
              value_from_integer_operand(signed_integral));
}

TEST_P(IntegerOperandSignedIntegralTest, SignAndValueFromArithmetic)
{
    auto signed_integral         = GetParam();
    auto expected_sign_and_value = std::make_pair(
        sign_from_signed_arithmetic(signed_integral),
        static_cast<std::uintmax_t>(std::abs(signed_integral))
    );

    EXPECT_EQ(expected_sign_and_value,
              sign_and_value_from_arithmetic(signed_integral));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    IntegerOperandSignedIntegralTest,
    ::testing::ValuesIn(tasty_int_test::SampleArithmetic<std::intmax_t>::VALUES)
);


class IntegerOperandFloatingPointTest
    : public ::testing::TestWithParam<long double>
{}; // class IntegerOperandFloatingPointTest

TEST_P(IntegerOperandFloatingPointTest, SignFromIntegerOperand)
{
    auto floating_point = GetParam();

    EXPECT_EQ(sign_from_signed_arithmetic(floating_point),
              sign_from_integer_operand(floating_point));
}

TEST_P(IntegerOperandFloatingPointTest, ValueFromIntegerOperand)
{
    auto floating_point = GetParam();

    EXPECT_EQ(std::abs(floating_point),
              value_from_integer_operand(floating_point));
}

TEST_P(IntegerOperandFloatingPointTest, SignAndValueFromArithmetic)
{
    auto floating_point          = GetParam();
    auto expected_sign_and_value = std::make_pair(
        sign_from_signed_arithmetic(floating_point),
        std::abs(floating_point)
    );

    EXPECT_EQ(expected_sign_and_value,
              sign_and_value_from_arithmetic(floating_point));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerArithmeticOperationTest,
    IntegerOperandFloatingPointTest,
    ::testing::ValuesIn(tasty_int_test::SampleArithmetic<long double>::VALUES)
);

} // namespace
