if(PROJECT_CMAKE_SET_HAVE_CHAR8_T_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_SET_HAVE_CHAR8_T_INCLUDED TRUE)
#[=======================================================================[.rst:
set_have_char8_t
----------------

This Module defines set_have_type():

::
set_have_char8_t(<target> <INTERFACE|PUBLIC|PRIVATE>)

which adds the following compile definitions/options to <target>:

    -DHAVE_CHAR8_T=<1|0>
        1 if char8_t is available, 0 otherwise.

    [ENABLE_CHAR8_T_COMPILE_OPTIONS]
        Enable C++ builtin type char8_t.  These options are provided only if
        available and required for char8_t support.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(set_have_type)

#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(set_have_char8_t target scope)
    set(initial_required_flags ${CMAKE_REQUIRED_FLAGS})
    set(candidate_compile_options "" "-fchar8_t")
    foreach(compile_option IN LISTS candidate_compile_options)
        set(CMAKE_REQUIRED_FLAGS ${initial_required_flags} ${compile_option})

        set_have_type(char8_t)

        if(HAVE_CHAR8_T)
            set(enable_char8_t_option ${compile_option})
            break()
        endif()
    endforeach()

    if(HAVE_CHAR8_T)
        message(STATUS "Found support for C++20 char8_t.")
        if(enable_char8_t_option)
            message(
                STATUS
                "Support for C++20 char8_t requires compile option"
                "'${enable_char8_t_option}' - enabling."
            )
            target_compile_options(
                ${target}
                ${scope}
                ${enable_char8_t_option}
            )
        endif()
    else()
        message(
            STATUS
            "No compiler support for C++20 char8_t.  Tried the following "
            "compile options: '${candidate_compile_options}'."
        )
    endif()

    target_compile_definitions(
        ${target}
        ${scope}
        -DHAVE_CHAR8_T=${HAVE_CHAR8_T}
    )
endfunction()
