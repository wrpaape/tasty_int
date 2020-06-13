#include "tasty_int_test/sample_arithmetic.hpp"

#include <limits>
#include <type_traits>
#include <set>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"


namespace {

using tasty_int_test::SampleArithmetic;


template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
class SampleArithmeticTest : public ::testing::Test
{
protected:
    static ArithmeticType
    get_middle(ArithmeticType lower_bound,
               ArithmeticType upper_bound)
    {
        // promote to long double to avoid overflow
        auto range = static_cast<long double>(upper_bound)
                   - static_cast<long double>(lower_bound);
        return lower_bound + static_cast<ArithmeticType>(range / 2.0L);
    }
}; // class SampleArithmeticTest


TYPED_TEST_SUITE(SampleArithmeticTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(SampleArithmeticTest, MinimumValue)
{
    EXPECT_EQ(std::numeric_limits<TypeParam>::lowest(),
              SampleArithmetic<TypeParam>::MINIMUM);
}

TYPED_TEST(SampleArithmeticTest, LowerQuartileValue)
{
    EXPECT_EQ(TestFixture::get_middle(SampleArithmetic<TypeParam>::MINIMUM,
                                      SampleArithmetic<TypeParam>::MEDIAN),
              SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(SampleArithmeticTest, MedianValue)
{
    auto expected = SampleArithmetic<TypeParam>::ZERO;
    if (std::is_unsigned_v<TypeParam>)
        expected =
            TestFixture::get_middle(SampleArithmetic<TypeParam>::MINIMUM,
                                    SampleArithmetic<TypeParam>::MAXIMUM);
    
    EXPECT_EQ(expected, SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(SampleArithmeticTest, UpperQuartileValue)
{
    EXPECT_EQ(TestFixture::get_middle(SampleArithmetic<TypeParam>::MEDIAN,
                                      SampleArithmetic<TypeParam>::MAXIMUM),
              SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(SampleArithmeticTest, MaximumValue)
{
    EXPECT_EQ(std::numeric_limits<TypeParam>::max(),
              SampleArithmetic<TypeParam>::MAXIMUM);
}

TYPED_TEST(SampleArithmeticTest, Zero)
{
    EXPECT_EQ(TypeParam(0), SampleArithmetic<TypeParam>::ZERO);
}

TYPED_TEST(SampleArithmeticTest, One)
{
    EXPECT_EQ(TypeParam(1), SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(SampleArithmeticTest, Values)
{
    std::set<TypeParam> values(
        SampleArithmetic<TypeParam>::VALUES.begin(),
        SampleArithmetic<TypeParam>::VALUES.end()
    );

    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::ZERO)           != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::ONE)            != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::MINIMUM)        != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::LOWER_QUARTILE) != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::MEDIAN)         != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::UPPER_QUARTILE) != values.end()
    );
    EXPECT_TRUE(
        values.find(SampleArithmetic<TypeParam>::MAXIMUM)        != values.end()
    );
}

} // namespace
