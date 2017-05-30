# output libraries to 'lib'
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

set(
    SOURCES
    tasty_int.cpp
    ${TASTY_INT_HEADERS}
)

add_library(${TASTY_INT_STATIC_LIBRARY} STATIC ${SOURCES})
add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${SOURCES})

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
