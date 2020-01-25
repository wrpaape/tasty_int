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
        add_custom_command(
            OUTPUT            ${CMAKE_CURRENT_LIST_DIR}/Doxygen
            COMMAND           ${DOXYGEN_EXECUTABLE} Doxyfile
            DEPENDS           ${CMAKE_CURRENT_LIST_DIR}/Doxyfile
            COMMENT           "generating documentation"
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        )
        add_custom_target(docs DEPENDS Doxygen)
    else()
        message("Missing ${missing_components} required to generate "
                "documentation; skipping.")
    endif()
endfunction()

add_docs_target()
