# output libraries
set(TASTY_INT_LIBRARY_DIR          ${PROJECT_LIB_DIR}/tasty_int)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TASTY_INT_LIBRARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TASTY_INT_LIBRARY_DIR})

set(
    SOURCES
    tasty_int.cpp
)

set(
    HEADERS
    ${TASTY_INT_INCLUDE_DIR}/tasty_int.hpp
)


add_library(${TASTY_INT_STATIC_LIBRARY} STATIC ${SOURCES} ${HEADERS})
add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${SOURCES} ${HEADERS})

add_subdirectory(test)
