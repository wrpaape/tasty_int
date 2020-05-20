if(PROJECT_CMAKE_TRY_LINK_LIBCXXABI_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_TRY_LINK_LIBCXXABI_INCLUDED TRUE)
#[=======================================================================[.rst:
try_link_libcxxabi
------------------

This Module defines ``try_link_libcxxabi``, which, if compiling with
[Apple]Clang, attempts to find and, if it is compatible, add libc++abi to the
link options in the current scope.  Typical usage:

::

    include(try_link_libcxxabi)
    try_link_libcxxabi()

#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(CheckCXXSourceCompiles)

# External API
# ------------------------------------------------------------------------------
function(try_link_libcxxabi)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(STATUS "Compiler is not [Apple]Clang; not linking libc++abi.")
        return()
    endif()

    find_library(libcxxabi c++abi)
    if(NOT libcxxabi)
        message(STATUS "Did not find libc++abi; skipping.")
        return()
    endif()

    message(STATUS "Found libc++abi: ${libcxxabi}.")
    list(APPEND CMAKE_REQUIRED_LIBRARIES ${libcxxabi})
    check_cxx_source_compiles(
        "int
         main()
         {
            return 0;
         }"
        link_libcxxabi
    )
    if(link_libcxxabi)
        message(STATUS "libc++abi is compatible; linking.")
        link_libraries(${libcxxabi})
    else()
        message(STATUS "libc++abi is not compatible; excluding.")
    endif()
endfunction()
