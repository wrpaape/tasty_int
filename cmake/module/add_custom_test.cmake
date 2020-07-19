if(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_custom_test
---------------

This Module defines ``add_custom_test``:

::

    add_custom_test(
        <NAME                          <name>>
        <SOURCES                       <srcs>>
        [INCLUDE_DIRECTORIES           <dirs>]
        [COMPILE_DEFINITIONS           <defs>]
        [COMPILE_OPTIONS               <opts>]
        [LIBRARIES                     <libs>]
        [DEPENDENCIES                  <deps>]
        [FRAMEWORK_NAME                <name>]
        [FRAMEWORK_SOURCES             <srcs>]
        [FRAMEWORK_INCLUDE_DIRECTORIES <dirs>]
        [FRAMEWORK_COMPILE_DEFINITIONS <defs>]
        [FRAMEWORK_COMPILE_OPTIONS     <opts>]
        [FRAMEWORK_LIBRARIES           <libs>]
        [FRAMEWORK_DEPENDENCIES        <deps>]
    )

which adds an executable target called <name> built according to the specified
parameters.  Parameters marked with the ``FRAMEWORK_`` prefix may be leveraged
by wrapper modules as a channel for injecting testing framework dependencies.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_executable)

# External API
# ------------------------------------------------------------------------------
function(add_custom_test)
    add_custom_executable(${ARGV})

    target_include_directories(
        ${CUSTOM_EXECUTABLE_NAME}
        PRIVATE
        ${PROJECT_TEST_INCLUDE_DIR}
    )

    add_test(
        NAME    ${CUSTOM_EXECUTABLE_NAME}
        COMMAND $<TARGET_FILE:${CUSTOM_EXECUTABLE_NAME}>
    )

    # append to dependencies of 'make build-test', etc...
    foreach(target ${PROJECT_BUILD_TEST_COMMANDS})
        add_dependencies(${target} ${CUSTOM_EXECUTABLE_NAME})
    endforeach()

    if(BUILD_COVERAGE)
        add_dependencies(coverage ${CUSTOM_EXECUTABLE_NAME})
    endif()
endfunction()
