if(PROJECT_CMAKE_ADD_THIRD_PARTY_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_THIRD_PARTY_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_third_party
---------------

This Module defines add_third_party():

::

    add_third_party(
        <INSTALL_PREFIX <dir> >
        [NAME           <name>]
    )

which configures, builds, and installs third_party packages during project
configuration time.  This expects to execute a CMakeLists.txt found at
the root of the ``${CMAKE_CURRENT_SOURCE_DIR}/third_party`` directory.  Build
artifacts may be found under ``INSTALL_PREFIX`` upon successful completion, 
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(parse_arguments)

# External API
# ------------------------------------------------------------------------------
function(add_third_party)
    set(boolean_keywords  "")
    set(value_keywords    INSTALL_PREFIX NAME)
    set(list_keywords     "")
    set(required_keywords INSTALL_PREFIX)
    parse_arguments(
        THIRD_PARTY # prefix
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

    # cmake fails to find the GIT_EXECUTABLE required for ExternalProject()
    # from the Visual Studio 2019 community edition git extension:
    #
    #     C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd
    # 
    # Use the CMAKE_COMMAND:
    #
    #     C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
    # 
    # to attempt to reconstruct the path to the GIT_EXECUTABLE.
    unset(check_git_paths)
    if(MSVC)
        set(ms_common_ext_path ${CMAKE_COMMAND})
        
        while(TRUE)
            get_filename_component(basename ${ms_common_ext_path} NAME)
            if(basename STREQUAL "Microsoft")
                set(check_git_paths
                    PATHS "${ms_common_ext_path}/TeamFoundation/Team Explorer/Git/cmd")
            endif()
            set(prev_path ${ms_common_ext_path})
            get_filename_component(ms_common_ext_path ${ms_common_ext_path} DIRECTORY)
            if(ms_common_ext_path STREQUAL prev_path)
                break()
            endif()
        endwhile()
    endif()
    find_program(GIT_EXECUTABLE git ${check_git_paths} REQUIRED)

    # avoid collisions with existing CMakeCache.txt's
    file(RELATIVE_PATH relative_root
        ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    set(binary_dir ${CMAKE_BINARY_DIR}/${relative_root}/third_party)
    make_directory(${binary_dir})

    set(configure_prompt "Configuring")
    set(configure_cmake_args 
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_INSTALL_PREFIX}
        -DGIT_EXECUTABLE:FILEPATH=${GIT_EXECUTABLE})

    set(build_prompt     "Building")
    set(build_cmake_args --build . --parallel)

    set(install_prompt     "Installing")
    set(install_cmake_args --install .)

    foreach(action configure build install)
        message(STATUS "${${action}_prompt} ${THIRD_PARTY_NAME}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} ${${action}_cmake_args}
            WORKING_DIRECTORY        ${binary_dir}
            RESULT_VARIABLE          result
            OUTPUT_VARIABLE          output
            ERROR_VARIABLE           output
        )
        if(result)
            message(SEND_ERROR  "Failed to ${action} ${THIRD_PARTY_NAME}.")
            message(FATAL_ERROR ${output})
        endif()
        message(STATUS "Success.")
    endforeach()
endfunction()
