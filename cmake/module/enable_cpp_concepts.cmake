if(PROJECT_CMAKE_ENABLE_CPP_CONCEPTS)
    return()
endif()
set(PROJECT_CMAKE_ENABLE_CPP_CONCEPTS TRUE)
# ------------------------------------------------------------------------------
#[=======================================================================[.rst:
enable_cpp_concepts
-------------------

Using C++20 concepts may require additional compiler options.  This Module
defines ``find_enable_cpp_concepts_compile_options``, which finds the compiler
options required to enable concepts, and ``enable_cpp_concepts``, which applies
them to the current scope. Either of these functions trigger a fatal error if
they fail to determine that the compiler has C++20 concepts support. Typical
usage:

::

    include(enable_cpp_concepts)
    ...
    find_enable_cpp_concepts_compile_options(enable_concepts)
    if(enable_concepts)
        target_compile_options(foo ${enable_concepts})
    endif()
    ...
    enable_cpp_concepts()

#]=======================================================================]
function(find_enable_cpp_concepts_compile_options enable_concepts_options)
    if(NOT FOUND_CPP_CONCEPTS_COMPILE_OPTIONS)
        set(binary_dir ${PROJECT_CMAKE_BINARY_DIR}/enable_cpp_concepts)
        set(src_dir    ${PROJECT_CMAKE_SRC_DIR}/enable_cpp_concepts)
        set(candidate_compile_options "" "-fconcepts" "-Xclang -fconcepts-ts")

        foreach(compile_option IN LISTS candidate_compile_options)
            try_compile(
                compile_option_compiled
                ${binary_dir}
                ${src_dir}/test_enable_cpp_concepts.cpp
                COMPILE_DEFINITIONS "${compile_option}" 
            )
            if(compile_option_compiled)
                set(ENABLE_CPP_CONCEPTS_COMPILE_OPTIONS "${compile_option}"
                    CACHE INTERNAL
                    "The compile option required to enable C++20 concepts.")
                break()
            endif()
        endforeach()

        if(NOT compile_option_compiled)
            message(
                FATAL_ERROR
                "No compiler support for C++20 concepts.  Tried the following "
                "compile options: '${candidate_compile_options}'."
            )
        endif()

        set(FOUND_CPP_CONCEPTS_COMPILE_OPTIONS TRUE CACHE INTERNAL
            "Guard to keep from re-running try_compile test.")
    endif()

    set(${enable_concepts_options}
        "${ENABLE_CPP_CONCEPTS_COMPILE_OPTIONS}"
        PARENT_SCOPE)
endfunction()

function(enable_cpp_concepts)
    find_enable_cpp_concepts_compile_options(enable_cpp_concepts_compile_options)
    if(enable_cpp_concepts_compile_options)
        message(
            STATUS
            "Setting required compile option for C++20 concepts support: "
            "'${enable_cpp_concepts_compile_options}'."
        )
        add_compile_options(${enable_cpp_concepts_compile_options})
    else()
        message(
            STATUS
            "No special compile options required for C++20 concepts support."
        )
    endif()
endfunction()
