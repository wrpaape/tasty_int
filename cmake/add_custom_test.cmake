if(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED)
    return()
endif(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED)
set(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED TRUE)
# ==============================================================================
# add a 'test_${NAME}' executable and CTest
# ==============================================================================

# External Dependencies
# ------------------------------------------------------------------------------
include(CMakeParseArguments)


# External API
# ------------------------------------------------------------------------------
function(add_custom_test)
    cmake_parse_arguments(
        CUSTOM_TEST                                                # prefix
        ""                                                         # booleans
        "FRAMEWORK_NAME;NAME"                                      # values
        "FRAMEWORK_SOURCES;FRAMEWORK_LIBRARIES;SOURCES;LIBRARIES;" # lists
        ${ARGN}                                                    # params
    )

    # check if framework supplied 'FRAMEWORK_NAME'
    if(NOT FRAMEWORK_NAME)
        message(FATAL_ERROR "missing 'FRAMEWORK_NAME'")
    endif(NOT FRAMEWORK_NAME)

    # check for required end user parameters
    foreach(REQUIRED NAME SOURCES)
        if("${CUSTOM_TEST_${REQUIRED}}" STREQUAL "")
            set(MISSING_REQUIRED
                "${MISSING_REQUIRED}${MISSING_SEPARTOR}${REQUIRED}")
            set(MISSING_SEPARTOR ", ")
        endif()
    endforeach(REQUIRED)

    if(MISSING_REQUIRED)
        message(
            FATAL_ERROR
            "missing required parameters \"${MISSING_REQUIRED}\" "
            "when trying to add a \"${FRAMEWORK_NAME}\" test"
        )
    endif(MISSING_REQUIRED)

    set(CUSTOM_TEST_TARGET test_${CUSTOM_TEST_NAME})

    add_executable(
        ${CUSTOM_TEST_TARGET}
        ${CUSTOM_TEST_SOURCES}
        ${FRAMEWORK_SOURCES}
    )

    if(CUSTOM_TEST_LIBRARIES OR FRAMEWORK_LIBRARIES)
        target_link_libraries(
            ${CUSTOM_TEST_TARGET}
            ${CUSTOM_TEST_LIBRARIES}
            ${FRAMEWORK_LIBRARIES}
        )
    endif(CUSTOM_TEST_LIBRARIES)

    set_target_properties(
        ${CUSTOM_TEST_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    target_include_directories(
        ${CUSTOM_TEST_TARGET}
        PUBLIC
        ${PROJECT_TEST_INCLUDE_DIR}
    )

    add_test(
        NAME              ${CUSTOM_TEST_NAME}
        COMMAND           $<TARGET_FILE:${CUSTOM_TEST_TARGET}>
        WORKING_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )
endfunction(add_catch_test)
