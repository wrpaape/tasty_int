if(PROJECT_CMAKE_INTRINSIC_COUNT_LEADING_ZEROS_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_INTRINSIC_COUNT_LEADING_ZEROS_INCLUDED TRUE)
#[=======================================================================[.rst:
set_intrinsic_count_leading_zeros
---------------------------------

This Module defines set_intrinsic_count_leading_zeros():

::
    set_intrinsic_count_leading_zeros(<target>)

which adds the following compile definitions to <target>:

    -DHAVE_INTRINSIC_COUNT_LEADING_ZEROS=<1|0>
        1 if an intrinsic "count leading zeros" function is available, 0
        otherwise.

    [-DINTRINSIC_COUNT_LEADING_ZEROS=<intrinsic function>]
        If -DHAVE_INTRINSIC_COUNT_LEADING_ZEROS=1, this macro will expand to
        the intrinsic "count leading zeros" function.
        
    [-DINTRINSIC_COUNT_LEADING_ZEROS_HEADER=<path/to/required/header>]
        If -DHAVE_INTRINSIC_COUNT_LEADING_ZEROS=1, and the intrinsic "count
        leading zeros" function requires a header, this macro will expand to
        the effect that

        #ifdef INTRINSIC_COUNT_LEADING_ZEROS_HEADER
        #   include INTRINSIC_COUNT_LEADING_ZEROS_HEADER
        #endif

        may be used in the <target> source to include it.

A "count leading zeros" function will return the number of 0-bits beyond the
most-significant 1-bit.
#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(check_intrinsic_count_leading_zeros clz header type1 type2 type3)
    set(binary_dir ${PROJECT_CMAKE_BINARY_DIR}/intrinsic_count_leading_zeros)
    set(src_dir    ${PROJECT_CMAKE_SRC_DIR}/intrinsic_count_leading_zeros)
    if("${header}" STREQUAL "")
        unset(header_definition)
    else()
        set(header_definition -DINTRINSIC_COUNT_LEADING_ZEROS_HEADER=${header})
    endif()

    try_run(
        run_result
        compile_result
        ${binary_dir}
        ${src_dir}/test_intrinsic_count_leading_zeros.cpp
        COMPILE_DEFINITIONS
        ${header_definition}
        -DINTRINSIC_COUNT_LEADING_ZEROS=${clz}
        -DINTRINSIC_OPERAND_TYPE1=${type1}
        -DINTRINSIC_OPERAND_TYPE2=${type2}
        -DINTRINSIC_OPERAND_TYPE3=${type3}
    )

    if(compile_result AND (run_result EQUAL 0))
        set(check_succeeded TRUE  PARENT_SCOPE)
    else()
        set(check_succeeded FALSE PARENT_SCOPE)
    endif()
endfunction()

function(find_intrinsic_count_leading_zeros)
    check_intrinsic_count_leading_zeros(__builtin_clz "" unsigned int "")
    if(check_succeeded)
        set(intrinsic_clz __builtin_clz PARENT_SCOPE)
        unset(intrinsic_clz_header PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zeros(__builtin_clzl "" unsigned long "")
    if(check_succeeded)
        set(intrinsic_clz __builtin_clzl PARENT_SCOPE)
        unset(intrinsic_clz_header PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zeros(__builtin_clzll "" unsigned long long)
    if(check_succeeded)
        set(intrinsic_clz __builtin_clzll PARENT_SCOPE)
        unset(intrinsic_clz_header PARENT_SCOPE)
        return()
    endif()

    set(intrin_header "<intrin.h>")

    check_intrinsic_count_leading_zeros(__lzcnt16 ${intrin_header} unsigned short "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt16        PARENT_SCOPE)
        set(intrinsic_clz_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zeros(__lzcnt ${intrin_header} unsigned int "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt          PARENT_SCOPE)
        set(intrinsic_clz_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zeros(__lzcnt64 ${intrin_header} unsigned __int64 "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt64        PARENT_SCOPE)
        set(intrinsic_clz_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    unset(intrinsic_clz        PARENT_SCOPE)
    unset(intrinsic_clz_header PARENT_SCOPE)
endfunction()

function(set_intrinsic_count_leading_zeros target)
    find_intrinsic_count_leading_zeros()

    if(intrinsic_clz)
        message(
            STATUS
            "Found intrinsic function for \"count leading zeros\": "
            "${intrinsic_clz}."
        )
        set(
            intrinsic_clz_compile_definitions
            -DHAVE_INTRINSIC_COUNT_LEADING_ZEROS=1
            -DINTRINSIC_COUNT_LEADING_ZEROS=${intrinsic_clz}
        )
        if(intrinsic_clz_header)
            message(
                STATUS
                "Found header required for intrinsic \"count leading zeros\": "
                "${intrinsic_clz_header}."
            )
            list(
                APPEND intrinsic_clz_compile_definitions
                -DINTRINSIC_COUNT_LEADING_ZEROS_HEADER=${intrinsic_clz_header}
            )
        endif()
    else()
        message(
            STATUS
            "Failed to find an intrinsic function for \"count leading zeros\"."
        )
        set(
            intrinsic_clz_compile_definitions
            -DHAVE_INTRINSIC_COUNT_LEADING_ZEROS=0
        )
    endif()

    target_compile_definitions(
        ${target}
        PRIVATE
        ${intrinsic_clz_compile_definitions}
    )
endfunction()
