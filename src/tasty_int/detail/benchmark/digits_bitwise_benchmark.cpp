#include <algorithm>

#include "benchmark/benchmark.h"

#include "tasty_int/detail/benchmark/digits_benchmark.hpp"


namespace {

using tasty_int::detail::digit_type;
using digits_benchmark::DigitsBenchmark;


class MutliplyDigitsByDigitBaseBenchmark : public DigitsBenchmark
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
        std::vector<digit_type> result(digits.size() + 1);

        benchmark::DoNotOptimize(result.data());

        std::copy(digits.begin(),
                  digits.end(),
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
        result.reserve(digits.size() + 1);

        benchmark::DoNotOptimize(result.data());

        result.emplace_back(0);
        result.insert(result.end(),
                      digits.begin(),
                      digits.end());

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBaseBenchmark, ReserveThenInsert)
    ->RangeMultiplier(MutliplyDigitsByDigitBaseBenchmark::RANGE_MULTIPLIER)
    ->Range(MutliplyDigitsByDigitBaseBenchmark::RANGE_FIRST,
            MutliplyDigitsByDigitBaseBenchmark::RANGE_LAST) 
    ->Unit(MutliplyDigitsByDigitBaseBenchmark::TIME_UNITS);


class MutliplyDigitsByDigitBasePowerInPlaceBenchmark : public DigitsBenchmark
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
        auto initial_size = digits.size();
        digits.resize(initial_size + exponent);

        benchmark::DoNotOptimize(digits.data());

        auto initial_end = digits.begin() + initial_size;
        std::copy_backward(digits.begin(),
                           initial_end,
                           digits.end());
        std::fill(digits.begin(), initial_end, 0);

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
        digits.resize(digits.size() + exponent);

        benchmark::DoNotOptimize(digits.data());

        auto initial_end = digits.rbegin() + exponent;
        std::swap_ranges(initial_end,
                         digits.rend(),
                         digits.rbegin());

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(MutliplyDigitsByDigitBasePowerInPlaceBenchmark,
                     ResizeThenSwapRanges)
    ->Apply(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::make_arguments)
    ->Unit(MutliplyDigitsByDigitBasePowerInPlaceBenchmark::TIME_UNITS);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
