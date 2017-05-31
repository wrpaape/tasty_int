# update include path
include_directories(${PROJECT_INCLUDE_DIR})

# set vars common to subdirectories
set(TASTY_INT_STATIC_LIBRARY tasty_int_static)
set(TASTY_INT_SHARED_LIBRARY tasty_int_shared)
set(TASTY_INT_INCLUDE_DIR    ${PROJECT_INCLUDE_DIR}/tasty_int)
file(
    GLOB_RECURSE
    TASTY_INT_HEADERS
    ${TASTY_INT_INCLUDE_DIR}/*.[h|i]pp
)


add_subdirectory(tasty_int)
add_subdirectory(tasty_int_demo)
