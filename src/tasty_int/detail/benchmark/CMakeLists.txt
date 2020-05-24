include(add_google_benchmark)

add_library(tasty_int-detail-digits_benchmark INTERFACE)
target_sources(
    tasty_int-detail-digits_benchmark
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/digits_benchmark.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_benchmark(
    NAME      tasty_int-detail-digits_bitwise_benchmark
    SOURCES   digits_bitwise_benchmark.cpp
    LIBRARIES tasty_int-detail-digits_benchmark
)

add_google_benchmark(
    NAME      tasty_int-detail-digits_multiplication_benchmark
    SOURCES   digits_multiplication_benchmark.cpp
    LIBRARIES tasty_int-detail-digits_multiplication
              tasty_int-detail-digits_benchmark
)
