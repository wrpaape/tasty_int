if(PROJECT_CMAKE_INTRINSIC_COUNT_LEADING_ZERO_BITS_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_INTRINSIC_COUNT_LEADING_ZERO_BITS_INCLUDED TRUE)
#[=======================================================================[.rst:
set_intrinsic_count_leading_zero_bits
-------------------------------------

This Module defines set_intrinsic_count_leading_zero_bits():

::
    set_intrinsic_count_leading_zero_bits(<target>)

which adds the following compile definitions to <target>:

    -DHAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS=<1|0>
        1 if an intrinsic "count leading zero bits" function is available, 0
        otherwise.

    [-DINTRINSIC_COUNT_LEADING_ZERO_BITS=<intrinsic function>]
    If -DHAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS=1, this macro will expand to
        the intrinsic "count leading zero bits" function.
        
    [-DINTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER=<path/to/required/header>]
    If -DHAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS=1, and the intrinsic "count
        leading zero bits" function requires a header, this macro will expand
        to the effect that

        #ifdef INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
        #   include INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
        #endif

        may be used in the <target> source to include it.

A "count leading zero bits" function will return the number of 0-bits beyond
the most-significant 1-bit.
#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(check_intrinsic_count_leading_zero_bits clz header type1 type2 type3)
    set(binary_dir ${PROJECT_CMAKE_BINARY_DIR}/intrinsic_count_leading_zero_bits)
    set(src_dir    ${PROJECT_CMAKE_SRC_DIR}/intrinsic_count_leading_zero_bits)
    if("${header}" STREQUAL "")
        unset(header_def)
    else()
        set(header_def -DINTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER=${header})
    endif()

    try_run(
        run_result
        compile_result
        ${binary_dir}
        ${src_dir}/test_intrinsic_count_leading_zero_bits.cpp
        COMPILE_DEFINITIONS
        ${header_def}
        -DINTRINSIC_COUNT_LEADING_ZERO_BITS=${clz}
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

function(find_intrinsic_count_leading_zero_bits)
    check_intrinsic_count_leading_zero_bits(__builtin_clz "" unsigned int "")
    if(check_succeeded)
        set(intrinsic_clz __builtin_clz PARENT_SCOPE)
        unset(intrinsic_clzb_header PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zero_bits(__builtin_clzl "" unsigned long "")
    if(check_succeeded)
        set(intrinsic_clz __builtin_clzl PARENT_SCOPE)
        unset(intrinsic_clzb_header PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zero_bits(__builtin_clzll "" unsigned long long)
    if(check_succeeded)
        set(intrinsic_clz __builtin_clzll PARENT_SCOPE)
        unset(intrinsic_clzb_header PARENT_SCOPE)
        return()
    endif()

    set(intrin_header "<intrin.h>")

    check_intrinsic_count_leading_zero_bits(__lzcnt16 ${intrin_header} unsigned short "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt16         PARENT_SCOPE)
        set(intrinsic_clzb_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zero_bits(__lzcnt ${intrin_header} unsigned int "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt           PARENT_SCOPE)
        set(intrinsic_clzb_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    check_intrinsic_count_leading_zero_bits(__lzcnt64 ${intrin_header} unsigned __int64 "")
    if(check_succeeded)
        set(intrinsic_clz        __lzcnt64         PARENT_SCOPE)
        set(intrinsic_clzb_header ${intrin_header} PARENT_SCOPE)
        return()
    endif()

    unset(intrinsic_clz         PARENT_SCOPE)
    unset(intrinsic_clzb_header PARENT_SCOPE)
endfunction()

function(set_intrinsic_count_leading_zero_bits target)
    find_intrinsic_count_leading_zero_bits()

    if(intrinsic_clz)
        message(
            STATUS
            "Found intrinsic function for \"count leading zero bits\": "
            "${intrinsic_clz}."
        )
        set(
            intrinsic_clzb_compile_definitions
            -DHAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS=1
            -DINTRINSIC_COUNT_LEADING_ZERO_BITS=${intrinsic_clz}
        )
        if(intrinsic_clzb_header)
            message(
                STATUS
                "Found header required for intrinsic \"count leading zero "
                "bits\": ${intrinsic_clzb_header}."
            )
            list(
                APPEND intrinsic_clzb_compile_definitions
                -DINTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER=${intrinsic_clzb_header}
            )
        endif()
    else()
        message(
            STATUS
            "Failed to find an intrinsic function for \"count leading zero "
            "bits\"."
        )
        set(
            intrinsic_clzb_compile_definitions
            -DHAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS=0
        )
    endif()

    target_compile_definitions(
        ${target}
        PRIVATE
        ${intrinsic_clzb_compile_definitions}
    )
endfunction()
