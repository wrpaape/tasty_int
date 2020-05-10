#include "tasty_int/detail/digits_multiplication.hpp"

#include "benchmark/benchmark.h"


namespace {

using tasty_int::detail::long_multiply;
using tasty_int::detail::karatsuba_multiply;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;


class MultiplyDigitsBenchmark : public benchmark::Fixture
{
public:
    void SetUp(benchmark::State &state) override;
    void TearDown(benchmark::State &state) override;

protected:
    std::vector<digit_type> lhs;
    std::vector<digit_type> rhs;
}; // class MultiplyDigitsBenchmark

void MultiplyDigitsBenchmark::SetUp(benchmark::State &state)
{
    auto size_digits = state.range(0);
    lhs.assign(size_digits, DIGIT_TYPE_MAX);
    rhs = lhs;
}

void MultiplyDigitsBenchmark::TearDown(benchmark::State &state)
{
    lhs.clear();
    rhs.clear();
}


BENCHMARK_DEFINE_F(MultiplyDigitsBenchmark, LongMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(long_multiply(lhs, rhs));
}
BENCHMARK_REGISTER_F(MultiplyDigitsBenchmark, LongMultiply)
    ->RangeMultiplier(2)
    ->Range(8, 8 << 11)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(MultiplyDigitsBenchmark, KaratsubaMultiply)(
    benchmark::State &state
)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(karatsuba_multiply(lhs, rhs));
}
BENCHMARK_REGISTER_F(MultiplyDigitsBenchmark, KaratsubaMultiply)
    ->RangeMultiplier(2)
    ->Range(8, 8 << 11)
    ->Unit(benchmark::kMillisecond);


// Run the benchmark
BENCHMARK_MAIN();

} // namespace
