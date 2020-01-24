include(cpp_restrict_qualifier) # set CPP_RESTRICT_QUALIFIER

# update compile definitions
add_definitions(-DCPP_RESTRICT_QUALIFIER=${CPP_RESTRICT_QUALIFIER})

# update compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# update include path
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
