# set vars used in cmake_tutorial and app
set(TASTY_INT_INCLUDE_DIR    ${PROJECT_INCLUDE_DIR}/tasty_int)
set(TASTY_INT_STATIC_LIBRARY libct_static)
set(TASTY_INT_SHARED_LIBRARY libct_shared)

add_subdirectory(tasty_int)
add_subdirectory(tasty_int_demo)

