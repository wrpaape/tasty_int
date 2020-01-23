# set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_TEST_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_TEST_LIB_DIR})

# set include directory
include_directories(${PROJECT_TEST_INCLUDE_DIR})

# enter
add_subdirectory(src)
