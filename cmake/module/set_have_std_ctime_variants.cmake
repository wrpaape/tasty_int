if(PROJECT_CMAKE_SET_HAVE_STD_CTIME_VARIANTS_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_SET_HAVE_STD_CTIME_VARIANTS_INCLUDED TRUE)
#[=======================================================================[.rst:
set_have_std_ctime_variants
---------------------------

This Module defines set_have_std_ctime_variants():

::

    set_have_std_ctime_variants(<target> <INTERFACE|PUBLIC|PRIVATE>)

which adds the following compile definitions to <target>:

    -DHAVE_CTIME_S=<1|0>
        1 if ctime_s is available, 0 otherwise.

    -DHAVE_CTIME_R=<1|0>
        1 if ctime_r is available, 0 otherwise.

    [-D__STDC_WANT_LIB_EXT1__=1]
        Enable ctime_s.  This definition is added only if ctime_s is available.
#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(set_have_std_ctime_variants target scope)
    if(NOT CHECKED_STD_CTIME_VARIANTS)
        set(binary_dir ${CMAKE_CURRENT_BINARY_DIR}/set_have_std_ctime_variants)
        set(src_dir    ${PROJECT_CMAKE_SRC_DIR}/set_have_std_ctime_variants)

        set(enable_ctime_s -D__STDC_WANT_LIB_EXT1__=1)
        try_compile(
            ctime_s_compiled
            ${binary_dir}
            ${src_dir}/test_have_ctime_s.cpp
            COMPILE_DEFINITIONS ${enable_ctime_s}
        )
        if(ctime_s_compiled)
            message(STATUS "Have support for ctime_s.")
            set(have_ctime_s 1)
        else()
            message(STATUS "Do not have support for ctime_s.")
            unset(enable_ctime_s)
            set(have_ctime_s 0)
        endif()

        try_compile(
            ctime_r_compiled
            ${binary_dir}
            ${src_dir}/test_have_ctime_r.cpp
        )
        if(ctime_r_compiled)
            message(STATUS "Have support for ctime_r.")
            set(have_ctime_r 1)
        else()
            message(STATUS "Do not have support for ctime_r.")
            set(have_ctime_r 0)
        endif()

        set(HAVE_STD_CTIME_VARIANTS_COMPILE_DEFINITIONS
            ${enable_ctime_s}
            -DHAVE_CTIME_S=${have_ctime_s}
            -DHAVE_CTIME_R=${have_ctime_r}
            CACHE INTERNAL
            "Defines presence/abscend of std::ctime variants.")
        set(CHECKED_STD_CTIME_VARIANTS TRUE CACHE INTERNAL
            "Guard to keep from re-running try_compile test.")
    endif()

    target_compile_definitions(
        ${target}
        ${scope}
        ${HAVE_STD_CTIME_VARIANTS_COMPILE_DEFINITIONS}
    )
endfunction()
