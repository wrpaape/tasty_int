include(add_google_benchmark)

add_library(${tasty_int-detail-}digits_benchmark INTERFACE)
target_sources(
    ${tasty_int-detail-}digits_benchmark
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/digits_benchmark.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_google_benchmark(
    NAME      ${CURRENT_NAMESPACE}digits_bitwise_benchmark
    SOURCES   digits_bitwise_benchmark.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_benchmark
)

add_google_benchmark(
    NAME      ${CURRENT_NAMESPACE}digits_multiplication_benchmark
    SOURCES   digits_multiplication_benchmark.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_multiplication
              ${CURRENT_NAMESPACE}digits_benchmark
)

add_google_benchmark(
    NAME      ${CURRENT_NAMESPACE}digits_division_benchmark
    SOURCES   digits_division_benchmark.cpp
    LIBRARIES ${CURRENT_NAMESPACE}digits_division
              ${CURRENT_NAMESPACE}digits_benchmark
              ${tasty_int-detail-conversions-}digits_from_integral
)

add_google_benchmark(
    NAME    ${CURRENT_NAMESPACE}sign_benchmark
    SOURCES sign_benchmark.cpp
            ${PROJECT_INCLUDE_DIR}/tasty_int/detail/sign.hpp
)

add_google_benchmark(
    NAME      ${CURRENT_NAMESPACE}extended_digit_accumulator_benchmark
    SOURCES   extended_digit_accumulator_benchmark.cpp
    LIBRARIES ${CURRENT_NAMESPACE}extended_digit_accumulator
)
