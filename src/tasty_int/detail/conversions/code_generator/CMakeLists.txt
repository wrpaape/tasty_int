include(std_filesystem_library)


add_library(
    tasty_int-detail-conversions-code_generator-table_generator
    OBJECT
    table_generator.cpp
    table_generator.hpp
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)

add_library(
    tasty_int-detail-conversions-code_generator-token_table_generator
    STATIC
    token_table_generator.cpp
    token_table_generator.hpp
    ${PROJECT_SRC_DIR}/tasty_int/detail/conversions/token_table.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-table_generator>
)

add_library(
    tasty_int-detail-conversions-code_generator-parse_code_generator_arguments
    OBJECT
    parse_code_generator_arguments.cpp
    parse_code_generator_arguments.hpp
)

add_library(
    tasty_int-detail-conversions-code_generator-generate_table_files
    STATIC
    generate_table_files.cpp
    generate_table_files.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-table_generator>
)
if(STD_FILESYSTEM_LIBRARY)
    target_link_libraries(
        tasty_int-detail-conversions-code_generator-generate_table_files
        ${STD_FILESYSTEM_LIBRARY}
    )
endif()

add_library(
    tasty_int-detail-conversions-code_generator-generate_token_table
    STATIC
    generate_token_table.cpp
    generate_token_table.hpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-parse_code_generator_arguments>
)
target_link_libraries(
    tasty_int-detail-conversions-code_generator-generate_token_table
    tasty_int-detail-conversions-code_generator-generate_table_files
    tasty_int-detail-conversions-code_generator-token_table_generator
)


function(generate_library code_generator target_name)
    set(codegen_dir ${CMAKE_CURRENT_LIST_DIR}/../codegen)

    set(target_header ${target_name}.hpp)
    set(target_source ${target_name}.cpp)
    set(target_files  ${codegen_dir}/${target_header}
                      ${codegen_dir}/${target_source})
    add_custom_command(
        OUTPUT  ${target_files}
        DEPENDS ${code_generator}
        COMMAND $<TARGET_FILE:${code_generator}> ${target_name} ${codegen_dir}
        COMMENT "Generating ${target_header} and ${target_source}."
    )
    add_library(
        tasty_int-detail-conversions-codegen-${target_name}
        OBJECT
        ${target_files}
    )
endfunction()


foreach(base 36 64)
    set(generate_token_table
        tasty_int-detail-conversions-code_generator-generate_base_${base}_token_table)
    add_executable(
        ${generate_token_table}
        generate_base_${base}_token_table.cpp
    )
    target_link_libraries(
        ${generate_token_table}
        tasty_int-detail-conversions-code_generator-generate_token_table
        tasty_int-detail-conversions-code_generator-token_table_generator
    )
    set(token_table_name base_${base}_token_values)
    generate_library(${generate_token_table} ${token_table_name})
    target_sources(
        tasty_int-detail-conversions-codegen-${token_table_name}
        PUBLIC
        ${PROJECT_SRC_DIR}/tasty_int/detail/conversions/token_table.hpp
    )
endforeach()

add_executable(
    tasty_int-detail-conversions-code_generator-generate_digits_per_token_table
    generate_digits_per_token_table.cpp
    $<TARGET_OBJECTS:tasty_int-detail-conversions-code_generator-parse_code_generator_arguments>
    ${PROJECT_INCLUDE_DIR}/tasty_int/detail/digit_type.hpp
)
target_link_libraries(
    tasty_int-detail-conversions-code_generator-generate_digits_per_token_table
    tasty_int-detail-conversions-code_generator-generate_table_files
)
generate_library(
    tasty_int-detail-conversions-code_generator-generate_digits_per_token_table
    digits_per_token_table
)


if(BUILD_TESTING)
    add_subdirectory(test)
endif()
