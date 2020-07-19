# test_third_party
# ------------------------------------------------------------------------------
include(add_third_party)

set(TEST_THIRD_PARTY_INSTALL_PREFIX
    ${CMAKE_CURRENT_BINARY_DIR}/third_party)

add_third_party(
    NAME           "testing third party dependencies"
    INSTALL_PREFIX ${TEST_THIRD_PARTY_INSTALL_PREFIX}
)

set(GTest_ROOT ${TEST_THIRD_PARTY_INSTALL_PREFIX}
    CACHE PATH "Installation prefix of GTest.")

add_subdirectory(tasty_int_test)
