#include "tasty_int/detail/split_digits.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::split_digits;
using tasty_int::detail::digit_type;

template<std::size_t COUNT_PIECES>
struct SplitDigitsTestParam
{
    std::vector<digit_type>                           digits;
    std::vector<digit_type>::size_type                split_size;
    std::array<std::vector<digit_type>, COUNT_PIECES> expected_result;
}; // struct SplitDigitsTestParam

template<std::size_t COUNT_PIECES>
class SplitDigitsTest
    : public ::testing::TestWithParam<SplitDigitsTestParam<COUNT_PIECES>>
{
public:
    using TestParam = SplitDigitsTestParam<COUNT_PIECES>;

protected:
    auto
    split() const
    {
        const auto& digits = this->GetParam().digits;
        auto split_size    = this->GetParam().split_size;

        return split_digits<COUNT_PIECES>(digits, split_size);
    }

    const auto&
    expected_result() const
    {
        return this->GetParam().expected_result;
    }
}; // class SplitDigitsTest 


class SplitDigitsIdentityTest : public SplitDigitsTest<1>
{}; // class SplitDigitsIdentityTest

TEST_P(SplitDigitsIdentityTest, SingleSplitTest)
{
    const auto& [ expected ] = expected_result();
    
    auto [ result ] = split();

    EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    SplitDigitsTest,
    SplitDigitsIdentityTest,
    ::testing::ValuesIn(
        std::vector<SplitDigitsIdentityTest::TestParam> {
            {
                .digits          = { 1, 2, 3 },
                .split_size      = 0,
                .expected_result = { {
                    { 1, 2, 3 }
                } }
            },
            {
                .digits          = { 1, 2, 3, 4 },
                .split_size      = 4,
                .expected_result = { {
                    { 1, 2, 3, 4 }
                } }
            },
            {
                .digits          = { 0, 0, 0, 9 },
                .split_size      = 1,
                .expected_result = { {
                    { 0, 0, 0, 9 }
                } }
            }
        }
    )
);


class SplitDigitsIntoTwoPiecesTest : public SplitDigitsTest<2>
{}; // class SplitDigitsIntoTwoPiecesTest

TEST_P(SplitDigitsIntoTwoPiecesTest, SingleSplitTest)
{
    const auto& [ expected_low, expected_high ] = expected_result();
    
    auto [ low, high ] = split();

    EXPECT_EQ(expected_low,  low);
    EXPECT_EQ(expected_high, high);
}

INSTANTIATE_TEST_SUITE_P(
    SplitDigitsTest,
    SplitDigitsIntoTwoPiecesTest,
    ::testing::ValuesIn(
        std::vector<SplitDigitsIntoTwoPiecesTest::TestParam> {
            {
                .digits          = { 1, 2, 3 },
                .split_size      = 1,
                .expected_result = { {
                    { 1 },
                    { 2, 3 }
                } }
            },
            {
                .digits          = { 1, 2, 3, 4 },
                .split_size      = 3,
                .expected_result = { {
                    { 1, 2, 3 },
                    { 4 }
                } }
            },
            {
                .digits          = { 0, 0, 0, 9 },
                .split_size      = 2,
                .expected_result = { {
                    { 0 },
                    { 0, 9 }
                } }
            },
            {
                .digits          = { 0, 0, 0, 0, 0, 0, 9 },
                .split_size      = 6,
                .expected_result = { {
                    { 0 },
                    { 9 }
                } }
            }
        }
    )
);


class SplitDigitsIntoThreePiecesTest : public SplitDigitsTest<3>
{}; // class SplitDigitsIntoThreePiecesTest

TEST_P(SplitDigitsIntoThreePiecesTest, SingleSplitTest)
{
    const auto& [ expected_low, expected_mid, expected_high ]
        = expected_result();
    
    auto [ low, mid, high ] = split();

    EXPECT_EQ(expected_low,  low);
    EXPECT_EQ(expected_mid,  mid);
    EXPECT_EQ(expected_high, high);
}

INSTANTIATE_TEST_SUITE_P(
    SplitDigitsTest,
    SplitDigitsIntoThreePiecesTest,
    ::testing::ValuesIn(
        std::vector<SplitDigitsIntoThreePiecesTest::TestParam> {
            {
                .digits          = { 1, 2, 3 },
                .split_size      = 1,
                .expected_result = { {
                    { 1 },
                    { 2 },
                    { 3 }
                } }
            },
            {
                .digits          = { 1, 2, 3, 4, 5 },
                .split_size      = 2,
                .expected_result = { {
                    { 1, 2 },
                    { 3, 4 },
                    { 5 }
                } }
            },
            {
                .digits          = { 0, 1, 0, 0, 9 },
                .split_size      = 2,
                .expected_result = { {
                    { 0, 1 },
                    { 0 },
                    { 9 }
                } }
            },
            {
                .digits          = { 0, 0, 1, 0, 0, 0, 0, 7 },
                .split_size      = 3,
                .expected_result = { {
                    { 0, 0, 1 },
                    { 0 },
                    { 0, 7 }
                } }
            }
        }
    )
);


class SplitDigitsIntoFourPiecesTest : public SplitDigitsTest<4>
{}; // class SplitDigitsIntoFourPiecesTest

TEST_P(SplitDigitsIntoFourPiecesTest, SingleSplitTest)
{
    const auto& [
        expected_low, expected_mid_low, expected_mid_high, expected_high
    ] = expected_result();
    
    auto [ low, mid_low, mid_high, high ] = split();

    EXPECT_EQ(expected_low,      low);
    EXPECT_EQ(expected_mid_low,  mid_low);
    EXPECT_EQ(expected_mid_high, mid_high);
    EXPECT_EQ(expected_high,     high);
}

INSTANTIATE_TEST_SUITE_P(
    SplitDigitsTest,
    SplitDigitsIntoFourPiecesTest,
    ::testing::ValuesIn(
        std::vector<SplitDigitsIntoFourPiecesTest::TestParam> {
            {
                .digits          = { 1, 2, 3, 4 },
                .split_size      = 1,
                .expected_result = { {
                    { 1 },
                    { 2 },
                    { 3 },
                    { 4 }
                } }
            },
            {
                .digits          = { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                .split_size      = 2,
                .expected_result = { {
                    { 1, 2 },
                    { 3, 4 },
                    { 5, 6 },
                    { 7, 8, 9 }
                } }
            },
            {
                .digits          = { 0, 1, 0, 0, 9, 0, 0, 0, 0, 1 },
                .split_size      = 2,
                .expected_result = { {
                    { 0, 1 },
                    { 0 },
                    { 9 },
                    { 0, 0, 0, 1 }
                } }
            },
            {
                .digits          = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                .split_size      = 4,
                .expected_result = { {
                    { 0 },
                    { 0 },
                    { 0 },
                    { 0, 1 }
                } }
            }
        }
    )
);

} // namespace
