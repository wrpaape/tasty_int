# executable binaries are output to root 'bin' directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})

set(target tasty_int_demo)

set(
    sources
    ${target}.cpp
    ${TASTY_INT_HEADERS}
)

set(
    libraries
    ${TASTY_INT_STATIC_LIBRARY}
)


add_executable(${target} ${sources})
target_link_libraries(${target} ${libraries})
