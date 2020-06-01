if(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_CUSTOM_TEST_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_custom_test
---------------

This Module defines add_custom_test():

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
    add_custom_executable(
        ${ARGV}
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    target_include_directories(
        ${CUSTOM_EXECUTABLE_NAME}
        PRIVATE
        ${PROJECT_TEST_INCLUDE_DIR}
    )

    add_test(
        NAME              ${CUSTOM_EXECUTABLE_NAME}
        COMMAND           ${CUSTOM_EXECUTABLE_NAME}
        WORKING_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    # append to dependencies of 'make build-test', etc...
    foreach(target ${PROJECT_BUILD_TEST_COMMANDS})
        add_dependencies(${target} ${CUSTOM_EXECUTABLE_NAME})
    endforeach()

    if(BUILD_COVERAGE)
        if(MSVC)
            set(no_optimization /O0)
        else()
            set(no_optimization -O0)
        endif()
        target_compile_options(
            ${CUSTOM_EXECUTABLE_NAME}
            PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CXX_FLAGS_COVERAGE}>
            $<$<COMPILE_LANGUAGE:C>:${CMAKE_C_FLAGS_COVERAGE}>
            ${no_optimization}
        )
        if(CMAKE_LIBRARIES_COVERAGE)
            target_link_libraries(
                ${CUSTOM_EXECUTABLE_NAME}
                PRIVATE
                ${CMAKE_LIBRARIES_COVERAGE}
            )
        endif()
        if(CMAKE_EXE_LINKER_FLAGS_COVERAGE)
            target_link_options(
                ${CUSTOM_EXECUTABLE_NAME}
                PRIVATE
                ${CMAKE_EXE_LINKER_FLAGS_COVERAGE}
            )
        endif()

        add_dependencies(coverage ${CUSTOM_EXECUTABLE_NAME})
    endif()
endfunction()
