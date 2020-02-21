# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

set(TASTY_INT_SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

# build internal implementation
add_subdirectory(detail)

if(TODO_REMOVE)
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

# build tasty_int libraries
foreach(type STATIC SHARED)
    add_library(${TASTY_INT_${type}_LIBRARY} ${type} ${sources})
endforeach()

# generate the 'token_values' lookup definitions source file
set(target generate_tasty_int_token_values_file)
set(
    sources
    ${generate_src_dir}/${target}.cpp
)

add_executable(${target} ${sources})
set_target_properties(
    ${target}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${generate_bin_dir}
)
add_custom_command(
    OUTPUT            ${token_values_path}
    COMMAND           ${target} ${token_values_path}
    WORKING_DIRECTORY ${generate_bin_dir}
    DEPENDS           ${sources}
    COMMENT           "generate TastyInt 'BASE_<base>_TOKEN_VALUES' lookup "
                      "tables"
)

endif(TODO_REMOVE)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
