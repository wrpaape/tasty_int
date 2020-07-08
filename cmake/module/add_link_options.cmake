if(PROJECT_CMAKE_ADD_LINK_OPTIONS_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_LINK_OPTIONS_INCLUDED TRUE)
#[=======================================================================[.rst:
add_link_options
----------------

This Module defines ``add_link_options``:

::

    add_link_options(<option> ...)

which uses the native cmake command or emulates it for unsupported versions of
cmake.
#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(add_link_options)
    set(link_options ${ARGV})

    if(COMMAND _add_link_options)
        _add_link_options(${link_options})
    else()
        # ensure flags are not duplicated in CACHE on each configure
        foreach(linker_flags_kind EXE SHARED)
            set(linker_flags CMAKE_${linker_flags_kind}_LINKER_FLAGS)

            separate_arguments(${linker_flags})

            list(REMOVE_ITEM ${linker_flags} "${link_options}")

            list(APPEND ${linker_flags} "${link_options}")

            string(REPLACE ";" " " ${linker_flags} "${${linker_flags}}")
        endforeach()

        set(
            CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS}"
            CACHE STRING
            "Flags used by the linker during all build types."
            FORCE
        )
        set(
            CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS}"
            CACHE STRING
            "Flags used by the linker during the creation of shared libraries during all build types."
            FORCE
        )
    endif()
endfunction()
