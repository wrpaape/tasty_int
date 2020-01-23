if(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_ADD_GOOGLE_TEST_CMAKE_INCLUDED TRUE)
# ==============================================================================
# Add a 'test_${NAME}' executable and CTest from sources compiled with the
# Google Test/Mock framework.
# ==============================================================================
# External Dependencies
# ------------------------------------------------------------------------------
include(add_custom_test)

# Exported Variables
# ------------------------------------------------------------------------------
set(
    GOOGLE_TEST_LIBRARIES
    gtest
    gtest_main
    gmock
    gmock_main
)

# External API
# ------------------------------------------------------------------------------
function(add_google_test)
    add_custom_test(
        ${ARGV}
        FRAMEWORK_NAME      googletest
        FRAMEWORK_LIBRARIES ${GOOGLE_TEST_LIBRARIES}
    )
endfunction()
