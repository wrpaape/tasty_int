#include "tasty_int/detail/digits_division.hpp"

#include <limits>

#include "benchmark/benchmark.h"

#include "tasty_int/detail/benchmark/digits_benchmark.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"


namespace {

using tasty_int::detail::long_divide;
using tasty_int::detail::divide_and_conquer_divide;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::conversions::digits_from_integral;
using digits_benchmark::DigitsBenchmark;


class DigitsDivisionBenchmark : public DigitsBenchmark
{
public:
    static constexpr int RANGE_SIZE_MULTIPLIER      = 2;
    static constexpr int RANGE_SIZE_FIRST           = 8;
    static constexpr int RANGE_SIZE_LAST            = RANGE_SIZE_FIRST << 9;
    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kMillisecond;

    static void make_arguments(benchmark::internal::Benchmark *benchmark)
    {
        for (auto size_dividend = RANGE_SIZE_FIRST;
             size_dividend <= RANGE_SIZE_LAST;
             size_dividend *= RANGE_SIZE_MULTIPLIER) {
            for (auto size_divisor : { 1, size_dividend / 4, size_dividend / 2,
                 size_dividend })
                benchmark->Args({ size_dividend, size_divisor });
        }
    }

    void SetUp(benchmark::State &state) override
    {
        DigitsBenchmark::SetUp(state);

        auto divisor_size = state.range(1);
        divisor.assign(divisor_size, DIGIT_TYPE_MAX);
    }

    void TearDown(benchmark::State &state) override
    {
        DigitsBenchmark::TearDown(state);

        divisor.clear();
    }

protected:
    std::vector<digit_type> divisor;
}; // class DigitsDivisionBenchmark

BENCHMARK_DEFINE_F(DigitsDivisionBenchmark, LongDivide)(benchmark::State &state)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_divide(digits, divisor));
}
BENCHMARK_REGISTER_F(DigitsDivisionBenchmark, LongDivide)
    ->Apply(DigitsDivisionBenchmark::make_arguments)
    ->Unit(DigitsDivisionBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(DigitsDivisionBenchmark, DivideAndConquerDivide)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(divide_and_conquer_divide(digits, divisor));
}
BENCHMARK_REGISTER_F(DigitsDivisionBenchmark, DivideAndConquerDivide)
    ->Apply(DigitsDivisionBenchmark::make_arguments)
    ->Unit(DigitsDivisionBenchmark::TIME_UNITS);


class DigitsAndIntegralDivisionBenchmark : public DigitsBenchmark
{
public:
    static constexpr int RANGE_SIZE_MULTIPLIER      = 2;
    static constexpr int RANGE_SIZE_FIRST           = 8;
    static constexpr int RANGE_SIZE_LAST            = RANGE_SIZE_FIRST << 11;
    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kMicrosecond;

    static void make_arguments(benchmark::internal::Benchmark *benchmark)
    {
        for (auto size_dividend = RANGE_SIZE_FIRST;
             size_dividend <= RANGE_SIZE_LAST;
             size_dividend *= RANGE_SIZE_MULTIPLIER) {
            for (auto size_divisor : { 1, 2 })
                benchmark->Args({ size_dividend, size_divisor });
        }
    }

    void SetUp(benchmark::State &state) override
    {
        DigitsBenchmark::SetUp(state);

        auto divisor_size     = state.range(1);
        auto right_shift_size = std::numeric_limits<std::uintmax_t>::digits
                              - (divisor_size * DIGIT_TYPE_BITS);
        divisor               = std::numeric_limits<std::uintmax_t>::max()
                             >> right_shift_size;
    }

protected:
    std::uintmax_t divisor;
}; // class DigitsAndIntegralDivisionBenchmark

BENCHMARK_DEFINE_F(DigitsAndIntegralDivisionBenchmark, LongDivide)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_divide(digits, divisor));
}
BENCHMARK_REGISTER_F(DigitsAndIntegralDivisionBenchmark, LongDivide)
    ->Apply(DigitsAndIntegralDivisionBenchmark::make_arguments)
    ->Unit(DigitsAndIntegralDivisionBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(DigitsAndIntegralDivisionBenchmark, ConvertThenLongDivide)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_divide(digits,
                                             digits_from_integral(divisor)));
}
BENCHMARK_REGISTER_F(DigitsAndIntegralDivisionBenchmark, ConvertThenLongDivide)
    ->Apply(DigitsAndIntegralDivisionBenchmark::make_arguments)
    ->Unit(DigitsAndIntegralDivisionBenchmark::TIME_UNITS);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
