# test_third_party
# ------------------------------------------------------------------------------
include(add_third_party)

add_third_party(
    NAME "testing third party dependencies"
    INSTALL_PREFIX ${PROJECT_TEST_DIR}
)

add_subdirectory(tasty_int_test)
