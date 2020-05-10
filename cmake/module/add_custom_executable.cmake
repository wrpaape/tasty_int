if(PROJECT_CMAKE_ADD_CUSTOM_EXECUTABLE_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_CUSTOM_EXECUTABLE_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_custom_executable
---------------------

This Module defines add_custom_executable():

::
    add_custom_executable(
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
        [RUNTIME_OUTPUT_DIRECTORY      <dir> ]
    )

which adds an executable target called <name> built according to the specified
parameters.  Parameters marked with the ``FRAMEWORK_`` prefix may be leveraged
by wrapper modules as a channel for injecting framework dependencies.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(parse_arguments)

# External API
# ------------------------------------------------------------------------------
function(add_custom_executable)
    set( 
        boolean_keywords  ""
    )
    set(
        value_keywords    NAME
                          FRAMEWORK_NAME
                          RUNTIME_OUTPUT_DIRECTORY
    )
    set(
        list_keywords     SOURCES
                          INCLUDE_DIRECTORIES
                          COMPILE_DEFINITIONS
                          COMPILE_OPTIONS
                          LIBRARIES
                          DEPENDENCIES
                          FRAMEWORK_SOURCES
                          FRAMEWORK_INCLUDE_DIRECTORIES
                          FRAMEWORK_COMPILE_DEFINITIONS
                          FRAMEWORK_COMPILE_OPTIONS
                          FRAMEWORK_LIBRARIES
                          FRAMEWORK_DEPENDENCIES
    )
    set(
        required_keywords NAME
                          SOURCES
    )
    parse_arguments(
        CUSTOM_EXECUTABLE      # prefix
        "${boolean_keywords}"
        "${value_keywords}"
        "${list_keywords}"
        "${required_keywords}"
        ${ARGV}
    )

    # check for required end user parameters
    if(CUSTOM_EXECUTABLE_MISSING_REQUIRED_ARGUMENTS)
        if(CUSTOM_EXECUTABLE_FRAMEWORK_NAME)
            set(CUSTOM_EXECUTABLE_TYPE "\"${CUSTOM_EXECUTABLE_FRAMEWORK_NAME}\"")
        else()
            set(CUSTOM_EXECUTABLE_TYPE "custom")
        endif()
        message(
            FATAL_ERROR
            "add_custom_executable -- failed to add a ${CUSTOM_EXECUTABLE_TYPE} executable"
        )
    endif()

    add_executable(
        ${CUSTOM_EXECUTABLE_NAME}
        ${CUSTOM_EXECUTABLE_SOURCES}
        ${CUSTOM_EXECUTABLE_FRAMEWORK_SOURCES}
    )

    target_include_directories(
        ${CUSTOM_EXECUTABLE_NAME}
        PRIVATE
        ${CUSTOM_EXECUTABLE_INCLUDE_DIRECTORIES}
        ${CUSTOM_EXECUTABLE_FRAMEWORK_INCLUDE_DIRECTORIES}
        ${PROJECT_INCLUDE_DIR}
    )

    list(
        APPEND CUSTOM_EXECUTABLE_COMPILE_DEFINITIONS
        ${CUSTOM_EXECUTABLE_FRAMEWORK_COMPILE_DEFINITIONS}
    )
    if(CUSTOM_EXECUTABLE_COMPILE_DEFINITIONS)
        target_compile_definitions(
            ${CUSTOM_EXECUTABLE_NAME}
            PRIVATE
            ${CUSTOM_EXECUTABLE_COMPILE_DEFINITIONS}
        )
    endif()

    list(
        APPEND CUSTOM_EXECUTABLE_COMPILE_OPTIONS
        ${CUSTOM_EXECUTABLE_FRAMEWORK_COMPILE_OPTIONS}
    )
    if(CUSTOM_EXECUTABLE_COMPILE_OPTIONS)
        target_compile_options(
            ${CUSTOM_EXECUTABLE_NAME}
            PRIVATE
            ${CUSTOM_EXECUTABLE_COMPILE_OPTIONS}
        )
    endif()

    list(APPEND CUSTOM_EXECUTABLE_LIBRARIES ${CUSTOM_EXECUTABLE_FRAMEWORK_LIBRARIES})
    if(CUSTOM_EXECUTABLE_LIBRARIES)
        target_link_libraries(${CUSTOM_EXECUTABLE_NAME} ${CUSTOM_EXECUTABLE_LIBRARIES})
    endif()

    list(APPEND CUSTOM_EXECUTABLE_DEPENDENCIES ${CUSTOM_EXECUTABLE_FRAMEWORK_DEPENDENCIES})
    if(CUSTOM_EXECUTABLE_DEPENDENCIES)
        add_dependencies(${CUSTOM_EXECUTABLE_NAME} ${CUSTOM_EXECUTABLE_DEPENDENCIES})
    endif()

    if(CUSTOM_EXECUTABLE_RUNTIME_OUTPUT_DIRECTORY)
        set_target_properties(
            ${CUSTOM_EXECUTABLE_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CUSTOM_EXECUTABLE_RUNTIME_OUTPUT_DIRECTORY}
        )
    endif()

    set(CUSTOM_EXECUTABLE_NAME ${CUSTOM_EXECUTABLE_NAME} PARENT_SCOPE)
endfunction()
