find_package(Doxygen 1.8.0)

function(add_docs_target)
    unset(missing_components)
    if(NOT DOXYGEN_FOUND)
        set(missing_components "`doxygen` >= 1.8.0")
    endif()
    if(NOT DOXYGEN_DOT_FOUND)
        if(missing_components)
            set(missing_components "${missing_components} and")
        endif()
        set(missing_components "${missing_components} Graphviz `dot`")
    endif()

    if(NOT missing_components)
        set(doxygen_dir ${CMAKE_CURRENT_LIST_DIR}/Doxygen)
        add_custom_command(
            OUTPUT            ${doxygen_dir}
            COMMAND           ${DOXYGEN_EXECUTABLE} Doxyfile
            DEPENDS           ${CMAKE_CURRENT_LIST_DIR}/Doxyfile
            COMMENT           "Generating documentation."
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        )
    add_custom_target(docs DEPENDS ${doxygen_dir})
    add_custom_command(
        TARGET  docs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
            "Documentation available here: ${doxygen_dir}/html/index.html"
    )
    else()
        message("Missing ${missing_components} required to generate "
                "documentation; skipping.")
    endif()
endfunction()

add_docs_target()
