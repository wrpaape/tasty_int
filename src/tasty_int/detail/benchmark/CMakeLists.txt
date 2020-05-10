include(add_google_benchmark)


add_google_benchmark(
    NAME      tasty_int-detail-digits_multiplication_benchmark
    SOURCES   digits_multiplication_benchmark.cpp
    LIBRARIES tasty_int-detail-digits_multiplication
)
