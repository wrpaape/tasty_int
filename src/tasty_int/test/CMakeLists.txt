set(TARGET                         test_tasty_int)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_DIR})

set(
    SOURCES
    test_tasty_int.cpp
)

set(
    HEADERS
    ${TASTY_INT_INCLUDE_DIR}/tasty_int.hpp
)

set(
    LIBRARIES
    ${TASTY_INT_SHARED_LIBRARY}
)

add_executable(${TARGET} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET} ${LIBRARIES})
