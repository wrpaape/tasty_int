if(PROJECT_CMAKE_CPP_RESTRICT_QUALIFIER_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_CPP_RESTRICT_QUALIFIER_INCLUDED TRUE)
# ==============================================================================
# check C++ compiler's support for a 'restrict' extension keyword
# set CPP_RESTRICT_QUALIFIER to that keyword or empty string if not supported
# ==============================================================================
# Exported Variables
# ------------------------------------------------------------------------------
set(CPP_RESTRICT_QUALIFIER_SRC_DIR
    ${PROJECT_CMAKE_SRC_DIR}/cpp_restrict_qualifier)
set(CPP_RESTRICT_QUALIFIER_BUILD_DIR
    ${PROJECT_CMAKE_BUILD_DIR}/cpp_restrict_qualifier)


# External API
# ------------------------------------------------------------------------------
function(set_cpp_restrict_qualifier)
    set(supported_qualifier "")
    foreach(qualifer "__restrict__" "__restrict" "restrict")
        try_compile(
            qualifier_compiled
            ${CPP_RESTRICT_QUALIFIER_BUILD_DIR}
            ${CPP_RESTRICT_QUALIFIER_SRC_DIR}/test_cpp_restrict_qualifier.cpp
            COMPILE_DEFINITIONS "-DCPP_RESTRICT_QUALIFIER=${qualifer}"
            OUTPUT_VARIABLE OOGA
        )

        if(qualifier_compiled)
            set(supported_qualifier ${qualifer})
            break()
        endif()
    endforeach()

    set(CPP_RESTRICT_QUALIFIER ${supported_qualifier} PARENT_SCOPE)
endfunction()
