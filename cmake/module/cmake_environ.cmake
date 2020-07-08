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
include(add_link_options)

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
   (CMAKE_BUILD_TYPE_LOWER STREQUAL "relwithdebinfo") OR
   (CMAKE_BUILD_TYPE_LOWER STREQUAL "minsizerel"))
   enable_interprocedural_optimization()
endif()
if(ENABLE_ADDRESS_SANITIZER AND ENABLE_UNDEFINED_BEHAVIOR_SANITIZER)
    message(
        FATAL_ERROR
        "Cannot enable AddressSanitizer and UndefinedBehaviorSanitizer at the "
        "same time."
    )
elseif(ENABLE_ADDRESS_SANITIZER)
    message(STATUS "Enabling AddressSanitizer.")
    add_compile_options(-fsanitize=address)
    add_link_options(   -fsanitize=address)
elseif(ENABLE_UNDEFINED_BEHAVIOR_SANITIZER)
    message(STATUS "Enabling UndefinedBehaviorSanitizer.")
    add_compile_options(-fsanitize=undefined)
    add_link_options(   -fsanitize=undefined)
endif()
if(MSVC)
    # Disable warning C4146: unary minus operator applied to unsigned type,
    # result still unsigned.
    add_compile_options(/wd4146)
    # Build with multiple processes. This option also enables synchronous PDB
    # writes ('/FS'), which is required for debug builds.
    add_compile_options(/MP)
endif()
