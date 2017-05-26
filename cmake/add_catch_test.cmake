if(PROJECT_CMAKE_ADD_CATCH_TEST_CMAKE_INCLUDED)
    return()
endif(PROJECT_CMAKE_ADD_CATCH_TEST_CMAKE_INCLUDED)
set(PROJECT_CMAKE_ADD_CATCH_TEST_CMAKE_INCLUDED TRUE)
# ==============================================================================
# add a 'test_${NAME}' executable and CTest from sources compiled with the Catch
# Test framework
# ==============================================================================

# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_test)


# Exported Variables
# ------------------------------------------------------------------------------
set(CATCH_TEST_DIR    ${PROJECT_TEST_INCLUDE_DIR}/catch)
set(CATCH_TEST_HEADER ${CATCH_TEST_DIR}/catch.hpp)


# Set Up Framework
# ------------------------------------------------------------------------------
# create directory in test/include
file(MAKE_DIRECTORY ${CATCH_TEST_DIR})

# download latest version of 'catch'
file(
    DOWNLOAD
    https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
    ${CATCH_TEST_HEADER}
)


# External API
# ------------------------------------------------------------------------------
function(add_catch_test)
    add_custom_test(
        FRAMEWOK_NAME     catch
        FRAMEWORK_SOURCES ${CATCH_TEST_HEADER}
        ${ARGN}
    )
endfunction(add_catch_test)
