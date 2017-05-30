set(
    SOURCES
    tasty_int.cpp
    ${TASTY_INT_INCLUDE_DIR}/tasty_int.hpp
)

# build tasty_int libraries
add_library(${TASTY_INT_STATIC_LIBRARY} STATIC ${SOURCES})
add_library(${TASTY_INT_SHARED_LIBRARY} SHARED ${SOURCES})

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
