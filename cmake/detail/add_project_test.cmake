if(PROJECT_CMAKE_DETAIL_ADD_PROJECT_TEST_INCLUDED)
    return()
endif(PROJECT_CMAKE_DETAIL_ADD_PROJECT_TEST_INCLUDED)
set(PROJECT_CMAKE_DETAIL_ADD_PROJECT_TEST_INCLUDED)
    
set(CATCH_TEST_DIR    ${PROJECT_TEST_INCLUDE_DIR}/catch)
set(CATCH_TEST_HEADER ${CATCH_TEST_DIR}/catch.hpp)

# create directory in test/include
file(MAKE_DIRECTORY ${CATCH_TEST_DIR})

# download latest version of 'catch'
file(
    DOWNLOAD
    https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
    ${CATCH_TEST_HEADER}
)


include(CMakeParseArguments)

function(add_catch_test)
    cmake_parse_arguments(
        CATCH_TEST          # parsed params prefix
        ""                  # boolean params
        "NAME"              # value params
        "SOURCES;LIBRARIES" # list params
        ${ARGN}             # input params
    )

    foreach(REQUIRED NAME SOURCES)
        if("${CATCH_TEST_${REQUIRED}}" STREQUAL "")
            set(MISSING_REQUIRED "${MISSING_REQUIRED}${MISSING_SEPARTOR}${REQUIRED}")
            set(MISSING_SEPARTOR ", ")
        endif()
    endforeach(REQUIRED)

    if(MISSING_REQUIRED)
        message(
            FATAL_ERROR
            "missing required parameters '${MISSING_REQUIRED}'"
        )
    endif(MISSING_REQUIRED)

    set(CATCH_TEST_TARGET test_${CATCH_TEST_NAME})

    add_executable(
        ${CATCH_TEST_TARGET}
        ${CATCH_TEST_SOURCES}
        ${CATCH_TEST_HEADER}
    )

    if(CATCH_TEST_LIBRARIES)
        target_link_libraries(
            ${CATCH_TEST_TARGET}
            ${CATCH_TEST_LIBRARIES}
        )
    endif(CATCH_TEST_LIBRARIES)

    set_target_properties(
        ${CATCH_TEST_TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )

    target_include_directories(
        ${CATCH_TEST_TARGET}
        PUBLIC
        ${PROJECT_TEST_INCLUDE_DIR}
    )

    add_test(
        NAME              ${CATCH_TEST_NAME}
        COMMAND           $<TARGET_FILE:${CATCH_TEST_TARGET}>
        WORKING_DIRECTORY ${PROJECT_TEST_BIN_DIR}
    )
endfunction(add_catch_test)
