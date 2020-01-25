include(cpp_restrict_qualifier) # set CPP_RESTRICT_QUALIFIER

# set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# update compile definitions
add_definitions(-DCPP_RESTRICT_QUALIFIER=${CPP_RESTRICT_QUALIFIER})

# update include path
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

# set vars common to subdirectories
set(TASTY_INT_STATIC_LIBRARY tasty_int_static)
set(TASTY_INT_SHARED_LIBRARY tasty_int_shared)
set(TASTY_INT_INCLUDE_DIR    ${PROJECT_INCLUDE_DIR}/tasty_int)
set(
    TASTY_INT_HEADERS
    ${TASTY_INT_INCLUDE_DIR}/tasty_int.hpp
    ${TASTY_INT_INCLUDE_DIR}/tasty_int.ipp
    ${TASTY_INT_INCLUDE_DIR}/detail/get_digit.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/from_arithmetic.hpp
    ${TASTY_INT_INCLUDE_DIR}/detail/to_arithmetic.hpp
)


add_subdirectory(tasty_int)
add_subdirectory(tasty_int_demo)
