# executable binaries are output to root 'bin' directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})

set(TARGET tasty_int_demo)

set(
    SOURCES
    ${TARGET}.cpp
    ${TASTY_INT_HEADERS}
)

set(
    LIBRARIES
    ${TASTY_INT_STATIC_LIBRARY}
)


add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${LIBRARIES})
