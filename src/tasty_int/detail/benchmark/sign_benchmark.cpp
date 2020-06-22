#include <cstdint>

#include <limits>

#include "benchmark/benchmark.h"

#include "tasty_int/detail/sign.hpp"


namespace {

using tasty_int::detail::Sign;


class ApplySignBenchmark : public benchmark::Fixture
{
protected:
    void SetUp(benchmark::State &state) override
    {
        benchmark::Fixture::SetUp(state);

        value = std::numeric_limits<std::uintmax_t>::max();
        sign  = static_cast<Sign>(state.range(0));
    }

    std::uintmax_t value = 0;
    Sign           sign  = Sign::ZERO;

}; // class ApplySignBenchmark

BENCHMARK_DEFINE_F(ApplySignBenchmark, NegateConditionally) (
    benchmark::State &state
)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(&value);

        if (sign < 0)
            value = -value;

        sign = -sign;

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(ApplySignBenchmark, NegateConditionally)
    ->Arg(Sign::NEGATIVE)
    ->Arg(Sign::ZERO)
    ->Arg(Sign::POSITIVE);

BENCHMARK_DEFINE_F(ApplySignBenchmark, MultiplyUnconditionally) (
    benchmark::State &state
)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(&value);

        value *= sign;

        sign = -sign;

        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_F(ApplySignBenchmark, MultiplyUnconditionally)
    ->Arg(Sign::NEGATIVE)
    ->Arg(Sign::ZERO)
    ->Arg(Sign::POSITIVE);

} // namespace


// Run the benchmark
BENCHMARK_MAIN();
