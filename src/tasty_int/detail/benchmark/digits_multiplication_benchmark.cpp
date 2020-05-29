#include "tasty_int/detail/digits_multiplication.hpp"

#include "benchmark/benchmark.h"

#include "tasty_int/detail/benchmark/digits_benchmark.hpp"


namespace {

using tasty_int::detail::long_multiply;
using tasty_int::detail::karatsuba_multiply;
using tasty_int::detail::digit_type;
using digits_benchmark::DigitsBenchmark;


class DigitsMultiplicationBenchmark : public DigitsBenchmark
{
public:
    static constexpr int RANGE_MULTIPLIER           = 2;
    static constexpr int RANGE_FIRST                = 8;
    static constexpr int RANGE_LAST                 = RANGE_FIRST << 11;
    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kMillisecond;

    void SetUp(benchmark::State &state) override
    {
        DigitsBenchmark::SetUp(state);

        multiplier = digits;
    }

    void TearDown(benchmark::State &state) override
    {
        DigitsBenchmark::TearDown(state);

        multiplier.clear();
    }

protected:
    std::vector<digit_type> multiplier;
}; // class DigitsMultiplicationBenchmark

BENCHMARK_DEFINE_F(DigitsMultiplicationBenchmark, LongMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_multiply(digits, multiplier));
}
BENCHMARK_REGISTER_F(DigitsMultiplicationBenchmark, LongMultiply)
    ->RangeMultiplier(DigitsMultiplicationBenchmark::RANGE_MULTIPLIER)
    ->Range(DigitsMultiplicationBenchmark::RANGE_FIRST,
            DigitsMultiplicationBenchmark::RANGE_LAST) 
    ->Unit(DigitsMultiplicationBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(DigitsMultiplicationBenchmark, KaratsubaMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(karatsuba_multiply(digits, multiplier));
}
BENCHMARK_REGISTER_F(DigitsMultiplicationBenchmark, KaratsubaMultiply)
    ->RangeMultiplier(DigitsMultiplicationBenchmark::RANGE_MULTIPLIER)
    ->Range(DigitsMultiplicationBenchmark::RANGE_FIRST,
            DigitsMultiplicationBenchmark::RANGE_LAST) 
    ->Unit(DigitsMultiplicationBenchmark::TIME_UNITS);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
