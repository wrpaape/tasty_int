if(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED)
    return()
endif()
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
    set(values FRAMEWORK_NAME
               NAME)
    set(lists FRAMEWORK_INCLUDE_DIRECTORIES
              FRAMEWORK_SOURCES
              FRAMEWORK_LIBRARIES
              SOURCES
              LIBRARIES)
    cmake_parse_arguments(
        CUSTOM_TEST # prefix
        ""          # booleans
        "${values}"
        "${lists}"
        ${ARGN}
    )

    # check for required end user parameters
    foreach(required NAME SOURCES)
        if("${CUSTOM_TEST_${required}}" STREQUAL "")
            set(missing_required
                "${missing_required}${missing_separator}${required}")
            set(missing_separator ", ")
        endif()
    endforeach()

    if(missing_required)
        if (NOT CUSTOM_TEST_FRAMEWORK_NAME)
            set(CUSTOM_TEST_FRAMEWORK_NAME "custom")
        endif()
        message(
            FATAL_ERROR
            "missing required parameters \"${missing_required}\" when trying to"
            " add a \"${CUSTOM_TEST_FRAMEWORK_NAME}\" test"
        )
    endif()

    set(CUSTOM_TEST_TARGET test_${CUSTOM_TEST_NAME})

    include_directories(
        ${CUSTOM_TEST_TARGET}
        PUBLIC
        ${PROJECT_INCLUDE_DIR}
        ${PROJECT_TEST_INCLUDE_DIR}
        ${CUSTOM_TEST_FRAMEWORK_INCLUDE_DIRECTORIES}
    )

    link_directories(${PROJECT_TEST_LIB_DIR})

    add_executable(
        ${CUSTOM_TEST_TARGET}
        ${CUSTOM_TEST_SOURCES}
        ${CUSTOM_TEST_FRAMEWORK_SOURCES}
    )

    if(CUSTOM_TEST_LIBRARIES OR CUSTOM_TEST_FRAMEWORK_LIBRARIES)
        target_link_libraries(
            ${CUSTOM_TEST_TARGET}
            ${CUSTOM_TEST_LIBRARIES}
            ${CUSTOM_TEST_FRAMEWORK_LIBRARIES}
        )
    endif()

    set_target_properties(
        ${CUSTOM_TEST_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    add_test(
        NAME              ${CUSTOM_TEST_NAME}
        COMMAND           ${CUSTOM_TEST_TARGET}
        WORKING_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    # append to dependencies of 'make run_tests'
    add_dependencies(${PROJECT_RUN_TESTS_TARGET} ${CUSTOM_TEST_TARGET})
endfunction()
