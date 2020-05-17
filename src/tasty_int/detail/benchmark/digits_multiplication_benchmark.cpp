#include "tasty_int/detail/digits_multiplication.hpp"

#include <algorithm>

#include "benchmark/benchmark.h"


namespace {

using tasty_int::detail::long_multiply;
using tasty_int::detail::karatsuba_multiply;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;


class MultiplyDigitsBenchmark : public benchmark::Fixture
{
public:
    void SetUp(benchmark::State &state) override
    {
        auto size_digits = state.range(0);
        multiplicand.assign(size_digits, DIGIT_TYPE_MAX);
    }

    void TearDown(benchmark::State &) override
    {
        multiplicand.clear();
    }

protected:
    std::vector<digit_type> multiplicand;
}; // class MultiplyDigitsBenchmark


class MutliplyDigitsByDigitBaseBenchmark : public MultiplyDigitsBenchmark
{
public:
    static constexpr int RANGE_MULTIPLIER           = 2;
    static constexpr int RANGE_FIRST                = 8;
    static constexpr int RANGE_LAST                 = RANGE_FIRST << 11;
    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kNanosecond;
}; // class MutliplyDigitsByDigitBaseBenchmark

BENCHMARK_DEFINE_F(MutliplyDigitsByDigitBaseBenchmark, ResizeThenCopy)(
    benchmark::State &state
)
{
    for (auto _ : state) {
        std::vector<digit_type> result(multiplicand.size() + 1);

        benchmark::DoNotOptimize(result.data());

        std::copy(multiplicand.begin(),
                  multiplicand.end(),
                  result.begin() + 1);

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBaseBenchmark, ResizeThenCopy)
    ->RangeMultiplier(MutliplyDigitsByDigitBaseBenchmark::RANGE_MULTIPLIER)
    ->Range(MutliplyDigitsByDigitBaseBenchmark::RANGE_FIRST,
            MutliplyDigitsByDigitBaseBenchmark::RANGE_LAST) 
    ->Unit(MutliplyDigitsByDigitBaseBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(MutliplyDigitsByDigitBaseBenchmark, ReserveThenInsert)(
    benchmark::State &state
)
{
    for (auto _ : state) {
        std::vector<digit_type> result;
        result.reserve(multiplicand.size() + 1);

        benchmark::DoNotOptimize(result.data());

        result.emplace_back(0);
        result.insert(result.end(),
                      multiplicand.begin(),
                      multiplicand.end());

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBaseBenchmark, ReserveThenInsert)
    ->RangeMultiplier(MutliplyDigitsByDigitBaseBenchmark::RANGE_MULTIPLIER)
    ->Range(MutliplyDigitsByDigitBaseBenchmark::RANGE_FIRST,
            MutliplyDigitsByDigitBaseBenchmark::RANGE_LAST) 
    ->Unit(MutliplyDigitsByDigitBaseBenchmark::TIME_UNITS);


class MutliplyDigitsByDigitBasePowerInPlaceBenchmark
    : public MultiplyDigitsBenchmark
{
public:
    static constexpr int RANGE_SIZE_MULTIPLIER      = 8;
    static constexpr int RANGE_SIZE_FIRST           = 8;
    static constexpr int RANGE_SIZE_LAST            = RANGE_SIZE_FIRST << 11;

    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kNanosecond;

    static void make_arguments(benchmark::internal::Benchmark *benchmark)
    {
        for (auto size = RANGE_SIZE_FIRST;
             size <= RANGE_SIZE_LAST; size *= RANGE_SIZE_MULTIPLIER) {
            for (auto exponent : { 1, size / 4, size / 2, size })
                benchmark->Args({ size, exponent });
        }
    }
}; // class MutliplyDigitsByDigitBasePowerInPlaceBenchmark

BENCHMARK_DEFINE_F(MutliplyDigitsByDigitBasePowerInPlaceBenchmark,
                   ResizeThenCopyBackwardAndFill) (
    benchmark::State &state
)
{
    auto exponent = state.range(1);

    for (auto _ : state) {
        auto initial_size = multiplicand.size();
        multiplicand.resize(initial_size + exponent);

        benchmark::DoNotOptimize(multiplicand.data());

        auto initial_end = multiplicand.begin() + initial_size;
        std::copy_backward(multiplicand.begin(),
                           initial_end,
                           multiplicand.end());
        std::fill(multiplicand.begin(), initial_end, 0);

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBasePowerInPlaceBenchmark,
                     ResizeThenCopyBackwardAndFill)
    ->Apply(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::make_arguments)
    ->Unit(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(MutliplyDigitsByDigitBasePowerInPlaceBenchmark,
                   ResizeThenSwapRanges) (
    benchmark::State &state
)
{
    auto exponent = state.range(1);

    for (auto _ : state) {
        multiplicand.resize(multiplicand.size() + exponent);

        benchmark::DoNotOptimize(multiplicand.data());

        auto initial_end = multiplicand.rbegin() + exponent;
        std::swap_ranges(initial_end,
                         multiplicand.rend(),
                         multiplicand.rbegin());

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBasePowerInPlaceBenchmark,
                     ResizeThenSwapRanges)
    ->Apply(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::make_arguments)
    ->Unit(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::TIME_UNITS);


class MultiplyDigitsByDigitsBenchmark : public MultiplyDigitsBenchmark
{
public:
    static constexpr int RANGE_MULTIPLIER           = 2;
    static constexpr int RANGE_FIRST                = 8;
    static constexpr int RANGE_LAST                 = RANGE_FIRST << 11;
    static constexpr benchmark::TimeUnit TIME_UNITS = benchmark::kMillisecond;

    void SetUp(benchmark::State &state) override
    {
        MultiplyDigitsBenchmark::SetUp(state);

        multiplier = multiplicand;
    }

    void TearDown(benchmark::State &state) override
    {
        MultiplyDigitsBenchmark::TearDown(state);

        multiplier.clear();
    }

protected:
    std::vector<digit_type> multiplier;
}; // class MultiplyDigitsByDigitsBenchmark

BENCHMARK_DEFINE_F(MultiplyDigitsByDigitsBenchmark, LongMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_multiply(multiplicand, multiplier));
}
BENCHMARK_REGISTER_F(MultiplyDigitsByDigitsBenchmark, LongMultiply)
    ->RangeMultiplier(MultiplyDigitsByDigitsBenchmark::RANGE_MULTIPLIER)
    ->Range(MultiplyDigitsByDigitsBenchmark::RANGE_FIRST,
            MultiplyDigitsByDigitsBenchmark::RANGE_LAST) 
    ->Unit(MultiplyDigitsByDigitsBenchmark::TIME_UNITS);

BENCHMARK_DEFINE_F(MultiplyDigitsByDigitsBenchmark, KaratsubaMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(karatsuba_multiply(multiplicand, multiplier));
}
BENCHMARK_REGISTER_F(MultiplyDigitsByDigitsBenchmark, KaratsubaMultiply)
    ->RangeMultiplier(MultiplyDigitsByDigitsBenchmark::RANGE_MULTIPLIER)
    ->Range(MultiplyDigitsByDigitsBenchmark::RANGE_FIRST,
            MultiplyDigitsByDigitsBenchmark::RANGE_LAST) 
    ->Unit(MultiplyDigitsByDigitsBenchmark::TIME_UNITS);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
