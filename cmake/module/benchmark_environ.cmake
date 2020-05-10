if(PROJECT_CMAKE_BENCHMARK_ENVIRON_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_BENCHMARK_ENVIRON_CMAKE_INCLUDED TRUE)
# ==============================================================================
# enable micro benchmarking
# ==============================================================================
# Exported Variables
# ------------------------------------------------------------------------------
# test directories
set(PROJECT_BENCHMARK_INCLUDE_DIR ${PROJECT_BENCHMARK_DIR}/include)
set(PROJECT_BENCHMARK_SRC_DIR     ${PROJECT_BENCHMARK_DIR}/src)
set(PROJECT_BENCHMARK_LIB_DIR     ${PROJECT_BENCHMARK_DIR}/lib)
set(PROJECT_BENCHMARK_BIN_DIR     ${PROJECT_BENCHMARK_DIR}/bin)


# Targets
# ------------------------------------------------------------------------------
# 'make benchmark' to build and run benchmarks
add_custom_target(benchmark)
