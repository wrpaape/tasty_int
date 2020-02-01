include(std_filesystem_library)

add_library(
    tasty_int-detail-code_generator-token_table_generator
    OBJECT
    token_table_generator.cpp
    token_table_generator.hpp
    ${TASTY_INT_DETAIL_DIR}/token_table.hpp
)

add_library(
    tasty_int-detail-code_generator-generate_token_table
    OBJECT
    generate_token_table.cpp
    generate_token_table.hpp
)
if(STD_FILESYSTEM_LIBRARY)
    target_link_libraries(
        tasty_int-detail-code_generator-generate_token_table
        ${STD_FILESYSTEM_LIBRARY}
    )
endif()

set(codegen_dir ${CMAKE_CURRENT_LIST_DIR}/../codegen)
foreach(base 36 64)
    set(generate_token_table
        tasty_int-detail-code_generator-generate_base_${base}_token_table)
    add_executable(
        ${generate_token_table}
        generate_base_${base}_token_table.cpp
        $<TARGET_OBJECTS:tasty_int-detail-code_generator-generate_token_table>
        $<TARGET_OBJECTS:tasty_int-detail-code_generator-token_table_generator>
    )
    
    set(token_table_name   base_${base}_token_values)
    set(token_table_header ${token_table_name}.hpp)
    set(token_table_source ${token_table_name}.cpp)
    set(token_table_files  ${codegen_dir}/${token_table_header}
                           ${codegen_dir}/${token_table_source})
    add_custom_command(
        OUTPUT  ${token_table_files}
        DEPENDS ${generate_token_table}
        COMMAND $<TARGET_FILE:${generate_token_table}>
                ${token_table_name} ${codegen_dir}
        COMMENT "Generating ${token_table_header} and ${token_table_source}."
    )
    add_library(
        tasty_int-detail-codegen-${token_table_name}
        OBJECT
        ${token_table_files}
        ${TASTY_INT_DETAIL_DIR}/token_table.hpp
    )
endforeach()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
