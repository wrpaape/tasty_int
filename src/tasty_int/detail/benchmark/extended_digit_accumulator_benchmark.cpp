#include <limits>

#include "benchmark/benchmark.h"

#include "tasty_int/detail/extended_digit_accumulator.hpp"


namespace {

using tasty_int::detail::ExtendedDigitAccumulator;
using tasty_int::detail::digit_accumulator_type;


class ExtendedDigitAccumulatorRightShiftBenchmark : public benchmark::Fixture
{
public:
    static constexpr int RANGE_FIRST = 0;
    static constexpr int RANGE_LAST  =
        std::numeric_limits<digit_accumulator_type>::digits - 1;
    static constexpr int RANGE_STEP  = RANGE_LAST / 4;

protected:
    void SetUp(benchmark::State &state) override
    {
        benchmark::Fixture::SetUp(state);

        bit_offset = static_cast<unsigned int>(state.range(0));
    }

    ExtendedDigitAccumulator accumulator = {{
        std::numeric_limits<digit_accumulator_type>::max(),
        std::numeric_limits<digit_accumulator_type>::max()
    }};
    unsigned int bit_offset = 0;

}; // class ApplySignBenchmark


ExtendedDigitAccumulator &
right_shift_with_test_for_zero_bit_offset(ExtendedDigitAccumulator &lhs,
                                          unsigned int              bit_offset)
{
    if (bit_offset == 0)
        return lhs;

    auto overflow_mask  =  (digit_accumulator_type(1) << bit_offset) - 1;
    auto overflow       = lhs.back() & overflow_mask;
    auto overflow_shift = std::numeric_limits<digit_accumulator_type>::digits
                        - bit_offset;

    lhs.front() >>= bit_offset;
    lhs.front()  |= (overflow << overflow_shift);
    lhs.back()  >>= bit_offset;

    return lhs;
}

BENCHMARK_DEFINE_F(ExtendedDigitAccumulatorRightShiftBenchmark,
                   TestForZeroBitOffset) (
    benchmark::State &state
)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(&accumulator);

        right_shift_with_test_for_zero_bit_offset(accumulator, bit_offset);

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(ExtendedDigitAccumulatorRightShiftBenchmark,
                     TestForZeroBitOffset)
    ->DenseRange(ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_FIRST,
                 ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_LAST,
                 ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_STEP);

ExtendedDigitAccumulator &
right_shift_with_mask_for_zero_bit_offset(ExtendedDigitAccumulator &lhs,
                                          unsigned int              bit_offset)
{
    auto overflow_mask =  (digit_accumulator_type(1) << bit_offset) - 1;
    auto overflow      = lhs.back() & overflow_mask;
    auto nonzero_bit_offset_mask = ((bit_offset == 0) - 1);
    auto overflow_shift = (std::numeric_limits<digit_accumulator_type>::digits &
                           nonzero_bit_offset_mask) - bit_offset;

    lhs.front() >>= bit_offset;
    lhs.front()  |= (overflow << overflow_shift);
    lhs.back()  >>= bit_offset;

    return lhs;
}

BENCHMARK_DEFINE_F(ExtendedDigitAccumulatorRightShiftBenchmark,
                   MaskForZeroBitOffset) (
    benchmark::State &state
)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(&accumulator);

        right_shift_with_mask_for_zero_bit_offset(accumulator, bit_offset);

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(ExtendedDigitAccumulatorRightShiftBenchmark,
                     MaskForZeroBitOffset)
    ->DenseRange(ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_FIRST,
                 ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_LAST,
                 ExtendedDigitAccumulatorRightShiftBenchmark::RANGE_STEP);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
