# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# base_XX_token_values lookup tables
set(TASTY_INT_TOKEN_VALUES_FILE
    ${CMAKE_CURRENT_LIST_DIR}/tasty_int_token_values.cpp)

set(
    sources
    tasty_int.cpp
    ${TASTY_INT_TOKEN_VALUES_FILE}
    ${TASTY_INT_HEADERS}
)

# build tasty_int libraries
add_library(${TASTY_INT_STATIC_LIBRARY} STATIC ${sources})
add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${sources})


# configuration 
add_subdirectory(configure)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
