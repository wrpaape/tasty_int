if(PROJECT_CMAKE_CMAKE_ENVIRON_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_CMAKE_ENVIRON_CMAKE_INCLUDED TRUE)
# ==============================================================================
# Set up common cmake environment.
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(enable_cpp_concepts)
include(enable_strict_compile_options)

# Exported Variables
# ------------------------------------------------------------------------------
set(PROJECT_CMAKE_SRC_DIR   ${PROJECT_CMAKE_DIR}/src)
set(PROJECT_CMAKE_BIN_DIR   ${PROJECT_CMAKE_DIR}/bin)
set(PROJECT_CMAKE_BUILD_DIR ${PROJECT_BUILD_DIR}/cmake)

# Enable common compile options
# ------------------------------------------------------------------------------
enable_cpp_concepts()
enable_strict_compile_options()
