if(PROJECT_CMAKE_ENABLE_CPP_CONCEPTS)
    return()
endif()
set(PROJECT_CMAKE_ENABLE_CPP_CONCEPTS TRUE)
# ------------------------------------------------------------------------------
#[=======================================================================[.rst:
enable_cpp_concepts
-------------------

Using C++20 concepts library may require additional compiler/linker options.
This Module defines ``enable_cpp_concepts``, which applies any required
compiler/linker options in the current scope. Typical usage:

::

    include(enable_cpp_concepts)
    enable_cpp_concepts()

#]=======================================================================]
function(enable_cpp_concepts)
    set(build_dir ${PROJECT_CMAKE_BUILD_DIR}/enable_cpp_concepts)
    set(src_dir   ${PROJECT_CMAKE_SRC_DIR}/enable_cpp_concepts)
    set(candidate_compile_options -fconcepts)
    foreach(compile_option "" ${candidate_compile_options})
        try_compile(
            compile_option_compiled
            ${build_dir}
            ${src_dir}/test_enable_cpp_concepts.cpp
            COMPILE_DEFINITIONS "${compile_option}" 
        )
        if(compile_option_compiled)
            set(enable_cpp_concepts_compile_option ${compile_option})
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

    if(enable_cpp_concepts_compile_option)
        message(
            STATUS
            "Setting required compile option for C++20 concepts support: "
            "'${enable_cpp_concepts_compile_option}'."
        )
        add_compile_options(${enable_cpp_concepts_compile_option})
    else()
        message(
            STATUS
            "No special compile options required for C++20 concepts support."
        )
    endif()
endfunction()
