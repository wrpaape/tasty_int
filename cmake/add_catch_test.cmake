if(PROJECT_CMAKE_ADD_CATCH_TEST_CMAKE_INCLUDED)
    return()
endif()
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
set(CATCH_TEST_SRC_DIR      ${PROJECT_TEST_SRC_DIR}/Catch)
set(CATCH_TEST_BUILD_DIR    ${PROJECT_BUILD_TEST_SRC_DIR}/Catch)
set(CATCH_TEST_INCLUDE_DIR  ${PROJECT_TEST_INCLUDE_DIR}/catch)
set(CATCH_TEST_HEADER       ${CATCH_TEST_INCLUDE_DIR}/catch.hpp)


# Set Up Framework
# ------------------------------------------------------------------------------
ExternalProject_Add(
    Catch
    GIT_REPOSITORY      https://github.com/philsquared/Catch.git
    GIT_TAG             master
    SOURCE_DIR          ${CATCH_TEST_SRC_DIR}
    BINARY_DIR          ${CATCH_TEST_BUILD_DIR}
    TEST_BEFORE_INSTALL ON
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${PROJECT_TEST_DIR}
)

# # create directory in test/include
# if(NOT EXISTS ${CATCH_TEST_DIR})
#     file(MAKE_DIRECTORY ${CATCH_TEST_DIR})
# endif()

# # download latest version of 'catch'
# if(NOT EXISTS ${CATCH_TEST_HEADER})
#     message(
#         STATUS
#         "Downloading 'Catch' header to: ${CATCH_TEST_HEADER}"
#     )
#     file(
#         DOWNLOAD
#         https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
#         ${CATCH_TEST_HEADER}
#         SHOW_PROGRESS
#     )
# endif()


# External API
# ------------------------------------------------------------------------------
function(add_catch_test)
    add_custom_test(
        ${ARGV}
        FRAMEWORK_NAME     Catch
        # FRAMEWORK_SOURCES  ${CATCH_TEST_HEADER}

    )
endfunction()
