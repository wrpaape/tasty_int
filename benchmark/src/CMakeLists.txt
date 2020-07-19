# benchmark_third_party
# ------------------------------------------------------------------------------
include(add_third_party)

set(BENCHMARK_THIRD_PARTY_INSTALL_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/third_party)

add_third_party(
    NAME           "benchmarking third party dependencies"
    INSTALL_PREFIX ${BENCHMARK_THIRD_PARTY_INSTALL_PREFIX}
)

set(benchmark_ROOT ${BENCHMARK_THIRD_PARTY_INSTALL_PREFIX}
    CACHE PATH "Installation prefix of benchmark.")
