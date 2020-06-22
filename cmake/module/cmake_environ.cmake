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
include(try_link_libcxxabi)
include(enable_interprocedural_optimization)

# Exported Variables
# ------------------------------------------------------------------------------
set(PROJECT_CMAKE_SRC_DIR    ${PROJECT_CMAKE_DIR}/src)
set(PROJECT_CMAKE_BIN_DIR    ${PROJECT_CMAKE_DIR}/bin)
set(PROJECT_CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/cmake)

# Enable common compile/link options
# ------------------------------------------------------------------------------
enable_cpp_concepts()
enable_strict_compile_options()
try_link_libcxxabi()
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if((CMAKE_BUILD_TYPE_LOWER STREQUAL "release") OR
   (CMAKE_BUILD_TYPE_LOWER STREQUAL "relwithdebinfo"))
   enable_interprocedural_optimization()
endif()
