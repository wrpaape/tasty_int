if(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED TRUE)
#[=======================================================================[.rst:
add_google_test
---------------

This Module defines add_google_test():

::
    add_google_test(
        <NAME                <name>>
        <SOURCES             <srcs>>
        [INCLUDE_DIRECTORIES <dirs>]
        [COMPILE_DEFINITIONS <defs>]
        [LIBRARIES           <libs>]
        [DEPENDENCIES        <deps>]
    )

which adds an executable target called <name> and links it to the googletest
framework.
#]=======================================================================]
# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_test)

# can't find GTest::* targets in CONFIG mode, fall back on MODULE mode
find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message(
        FATAL_ERROR
        "GTest should have been installed at the ${PROJECT_TEST_DIR} at this "
        "point. Check that ${PROJECT_TEST_DIR}/CMakeLists.txt has executed "
        "successfully before the current CMakeLists.txt: "
        "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt."
    )
endif()

# External API
# ------------------------------------------------------------------------------
function(add_google_test)
    add_custom_test(
        ${ARGV}
        FRAMEWORK_NAME      googletest
        FRAMEWORK_LIBRARIES GTest::GTest
                            GTest::Main
    )
endfunction()
