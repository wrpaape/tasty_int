# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# base_XX_token_values lookup tables
set(token_values_path
    ${CMAKE_CURRENT_LIST_DIR}/codegen/tasty_int_token_values.cpp)
set(
    sources
    tasty_int.cpp
    ${token_values_path}
    ${TASTY_INT_HEADERS}
)

# build tasty_int libraries
foreach(type STATIC SHARED)
    add_library(${TASTY_INT_${type}_LIBRARY} ${type} ${sources})
    target_include_directories(
        ${TASTY_INT_${type}_LIBRARY}
        INTERFACE
        ${PROJECT_INCLUDE_DIR}
    )
endforeach()
# add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${sources})


# configuration 
set(configure_dir     ${CMAKE_CURRENT_LIST_DIR}/configure)
set(configure_src_dir ${configure_dir}/src)
set(configure_bin_dir ${configure_dir}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${configure_bin_dir})

# generate the 'token_values' lookup definitions source file
set(target generate_tasty_int_token_values_file)
set(
    sources
    ${configure_src_dir}/${target}.cpp
    ${TASTY_INT_HEADERS}
)

add_executable(${target} ${sources})
add_custom_command(
    OUTPUT            ${token_values_path}
    COMMAND           ${target} ${token_values_path}
    WORKING_DIRECTORY ${configure_bin_dir}
    COMMENT           "generate TastyInt 'token_values' lookup tables"
)


if(BUILD_TESTING)
    add_subdirectory(test)
endif()
