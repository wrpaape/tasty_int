# benchmark_third_party
# ------------------------------------------------------------------------------
include(add_third_party)

add_third_party(
    NAME "benchmarking third party dependencies"
    INSTALL_PREFIX ${PROJECT_BENCHMARK_DIR}
)
