if(PROJECT_CMAKE_SET_HAVE_TYPE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_SET_HAVE_TYPE_INCLUDED TRUE)
# ==============================================================================
# TODO
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(CheckTypeSize)

# External API
# ------------------------------------------------------------------------------
function(set_have_type type)
    string(TOUPPER "${type}" uppercase_type)

    check_type_size(
        "${type}" "${uppercase_type}"
        BUILTIN_TYPES_ONLY
        LANGUAGE CXX
    )

    # convert TRUE/FALSE -> 1/0
    if (HAVE_${uppercase_type})
        set(have_type 1)
    else()
        set(have_type 0)
    endif()

    set(HAVE_${uppercase_type} ${have_type} PARENT_SCOPE)
endfunction()
