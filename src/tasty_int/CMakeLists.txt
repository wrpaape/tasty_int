include(cpp_restrict_qualifier) # set_cpp_restrict_qualifier
set_cpp_restrict_qualifier()

# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# code generation 
set(generate_dir         ${CMAKE_CURRENT_LIST_DIR}/generate)
set(generate_src_dir     ${generate_dir}/src)
set(generate_bin_dir     ${generate_dir}/bin)
set(generate_codegen_dir ${generate_dir}/codegen)

# base_XX_token_values lookup tables
set(token_values_path ${generate_codegen_dir}/tasty_int_token_values.cpp)

set(
    sources
    tasty_int.cpp
    ${token_values_path}
    ${TASTY_INT_HEADERS}
)

set(compile_definitions CPP_RESTRICT_QUALIFIER=${CPP_RESTRICT_QUALIFIER})

# build tasty_int libraries
foreach(type STATIC SHARED)
    add_library(${TASTY_INT_${type}_LIBRARY} ${type} ${sources})
    set_target_properties(
        ${TASTY_INT_${type}_LIBRARY}
        PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_INCLUDE_DIR}
        COMPILE_DEFINITIONS           ${compile_definitions}
    )
endforeach()
# add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${sources})


# generate the 'token_values' lookup definitions source file
set(target generate_tasty_int_token_values_file)
set(
    sources
    ${generate_src_dir}/${target}.cpp
    ${TASTY_INT_HEADERS}
)

add_executable(${target} ${sources})
set_target_properties(
    ${target}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${generate_bin_dir}
    COMPILE_DEFINITIONS      ${compile_definitions}
)
add_custom_command(
    OUTPUT            ${token_values_path}
    COMMAND           ${target} ${token_values_path}
    WORKING_DIRECTORY ${generate_bin_dir}
    COMMENT           "generate TastyInt 'token_values' lookup tables"
)


if(BUILD_TESTING)
    add_subdirectory(test)
endif()
