if(PROJECT_CMAKE_ADD_THIRD_PARTY_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_THIRD_PARTY_CMAKE_INCLUDED TRUE)
# ==============================================================================
# Calls ${CMAKE_COMMAND} to build a subdirectory 'third_party' containing
# external projects and install to 'INSTALL_PREFIX' during the configure step.
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(parse_arguments)

# External API
# ------------------------------------------------------------------------------
function(add_third_party)
    set(boolean_keywords  "")
    set(value_keywords    NAME INSTALL_PREFIX)
    set(list_keywords     "")
    set(required_keywords INSTALL_PREFIX)
    parse_arguments(
        THIRD_PARTY            # prefix
        "${boolean_keywords}"
        "${value_keywords}"
        "${list_keywords}"
        "${required_keywords}"
        ${ARGV}
    )

    # check for required end user parameters
    if(THIRD_PARTY_MISSING_REQUIRED_ARGUMENTS)
        message(
            FATAL_ERROR
            "add_third_party - Missing required INSTALL_PREFIX."
        )
    endif()
    if(NOT THIRD_PARTY_NAME)
        set(THIRD_PARTY_NAME "third party dependencies")
    endif()

    # avoid collisions with existing CMakeCache.txt's
    file(RELATIVE_PATH relative_root
        ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    set(binary_dir ${CMAKE_BINARY_DIR}/${relative_root}/third_party)

    # configure
    message(STATUS "Configuring ${THIRD_PARTY_NAME}...")
    make_directory(${binary_dir})
    execute_process(
        COMMAND           ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/third_party
                                           -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                                           -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_PREFIX}
        WORKING_DIRECTORY ${binary_dir}
        RESULT_VARIABLE   result
        OUTPUT_VARIABLE   output
        ERROR_VARIABLE    output
    )
    if(result)
        message(SEND_ERROR  "Failed to configure ${THIRD_PARTY_NAME}.")
        message(FATAL_ERROR ${output})
    endif()
    message(STATUS "Success.")

    # build
    message(STATUS "Building ${THIRD_PARTY_NAME}...")
    execute_process(
        COMMAND           ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${binary_dir}
        RESULT_VARIABLE   result
        OUTPUT_VARIABLE   output
        ERROR_VARIABLE    output
    )
    if(result)
        message(SEND_ERROR  "Failed to build ${THIRD_PARTY_NAME}.")
        message(FATAL_ERROR ${output})
    endif()
    message(STATUS "Success.")
endfunction()
