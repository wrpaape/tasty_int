# test_third_party
# ------------------------------------------------------------------------------
include(add_third_party)

add_third_party(
    NAME "testing third party dependencies"
    INSTALL_PREFIX ${PROJECT_TEST_DIR}
)
set(GTEST_ROOT ${PROJECT_TEST_DIR} CACHE PATH "Installation prefix of GTest.")

add_subdirectory(tasty_int_test)
