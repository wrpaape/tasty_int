if(PROJECT_CMAKE_ADD_CUSTOM_BENCHMARK_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_CUSTOM_BENCHMARK_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_custom_benchmark
--------------------

This Module defines add_custom_benchmark():

::
    add_custom_benchmark(
        <NAME                          <name>>
        <SOURCES                       <srcs>>
        [INCLUDE_DIRECTORIES           <dirs>]
        [COMPILE_DEFINITIONS           <defs>]
        [COMPILE_OPTIONS               <opts>]
        [LIBRARIES                     <libs>]
        [DEPENDENCIES                  <deps>]
        [FRAMEWORK_NAME                <name>]
        [FRAMEWORK_SOURCES             <srcs>]
        [FRAMEWORK_INCLUDE_DIRECTORIES <dirs>]
        [FRAMEWORK_COMPILE_DEFINITIONS <defs>]
        [FRAMEWORK_COMPILE_OPTIONS     <opts>]
        [FRAMEWORK_LIBRARIES           <libs>]
        [FRAMEWORK_DEPENDENCIES        <deps>]
    )

which adds an executable target called <name> built according to the specified
parameters.  Parameters marked with the ``FRAMEWORK_`` prefix may be leveraged
by wrapper modules as a channel for injecting benchmark framework dependencies.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_executable)

# External API
# ------------------------------------------------------------------------------
function(add_custom_benchmark)
    add_custom_executable(
        ${ARGV}
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BENCHMARK_BIN_DIR}
    )

    target_include_directories(
        ${CUSTOM_EXECUTABLE_NAME}
        PRIVATE
        ${PROJECT_BENCHMARK_INCLUDE_DIR}
    )

    set(echo_command ${CMAKE_COMMAND} -E cmake_echo_color --cyan)
    set(echo_line_command ${echo_command} ================================================================================)
    set(run_custom_benchmark_target run_benchmark-${CUSTOM_EXECUTABLE_NAME})

    add_custom_target(
        ${run_custom_benchmark_target}
        COMMAND           ${echo_command}
        COMMAND           ${echo_line_command}
        COMMAND           ${echo_command} "Running Benchmark: ${CUSTOM_EXECUTABLE_NAME}"
        COMMAND           ${echo_line_command}
        COMMAND           $<TARGET_FILE:${CUSTOM_EXECUTABLE_NAME}>
        COMMAND           ${echo_line_command}
        WORKING_DIRECTORY ${PROJECT_BENCHMARK_BIN_DIR}
    )

    # append to dependencies of 'make benchmark'
    add_dependencies(benchmark ${run_custom_benchmark_target})
endfunction()
