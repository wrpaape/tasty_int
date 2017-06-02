# executable binaries are output to config 'bin' directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# build configuration executables
add_subdirectory(src)
