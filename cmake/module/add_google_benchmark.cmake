if(PROJECT_CMAKE_ADD_GOOGLE_BENCHMARK_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_GOOGLE_BENCHMARK_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_google_benchmark
--------------------

This Module defines add_google_benchmark():

::
    add_google_benchmark(
        <NAME                <name>>
        <SOURCES             <srcs>>
        [INCLUDE_DIRECTORIES <dirs>]
        [COMPILE_DEFINITIONS <defs>]
        [LIBRARIES           <libs>]
        [DEPENDENCIES        <deps>]
    )

which adds an executable target called <name> and links it to the google
benchmark framework.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_benchmark)

find_package(
    benchmark REQUIRED
    PATHS ${PROJECT_BENCHMARK_DIR}
)
if(NOT benchmark_FOUND)
    message(
        FATAL_ERROR
        "benchmark should have been installed under ${PROJECT_BENCHMARK_DIR} at
        this point. Check that ${PROJECT_BENCHMARK_DIR}/CMakeLists.txt has
        executed successfully before the current CMakeLists.txt: "
        "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt."
    )
endif()

# External API
# ------------------------------------------------------------------------------
function(add_google_benchmark)
    if(NOT MSVC)
        # benchmark::Fixture is in the process of depreciating its
        # SetUp/TearDown interface, and at the moment a "new" and "old" pair of
        # function virtual signatures exist side-by-side.  This will generate a
        # warning if '-Woverloaded-virtual' is enabled => disable it to be sure.
        set(google_benchmark_compile_options -Wno-overloaded-virtual)
    endif()

    add_custom_benchmark(
        ${ARGV}
        FRAMEWORK_NAME            benchmark
        FRAMEWORK_LIBRARIES       benchmark::benchmark
                                  benchmark::benchmark_main
        FRAMEWORK_COMPILE_OPTIONS ${google_benchmark_compile_options}
    )
endfunction()
