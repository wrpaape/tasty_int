#include <vector>

#include "benchmark/benchmark.h"

#include "tasty_int/detail/digit_type.hpp"


namespace digits_benchmark {

class DigitsBenchmark : public benchmark::Fixture
{
public:
    void SetUp(benchmark::State &state) override
    {
        auto size_digits = state.range(0);
        digits.assign(size_digits, tasty_int::detail::DIGIT_TYPE_MAX);
    }

    void TearDown(benchmark::State &) override
    {
        digits.clear();
    }

protected:
    std::vector<tasty_int::detail::digit_type> digits;
}; // class DigitsBenchmark

} // namespace digits_benchmark
