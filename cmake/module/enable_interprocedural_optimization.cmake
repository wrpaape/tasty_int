if(PROJECT_CMAKE_ENABLE_INTERPROCEDURAL_OPTIMIZATION)
    return()
endif()
set(PROJECT_CMAKE_ENABLE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# ------------------------------------------------------------------------------
#[=======================================================================[.rst:
enable_interprocedural_optimization
-------------------
This Module defines ``enable_interprocedural_optimization``, which enables
interprocedural (link-time) optimization if supported. Typical usage:

::

    include(enable_interprocedural_optimization)
    enable_interprocedural_optimization()

#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(CheckIPOSupported)

# External API
# ------------------------------------------------------------------------------
function(enable_interprocedural_optimization)
    check_ipo_supported(
        RESULT have_ipo_support
        OUTPUT ipo_unsupported_error
    )
    if(have_ipo_support)
        message(STATUS "Have interprocedural optimization; enabling.")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE PARENT_SCOPE)
    else()
        message(
            STATUS
            "Do not have interprocedural optimization: "
            "${ipo_unsupported_error}; skipping."
        )
    endif()
endfunction()
