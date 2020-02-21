# set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# update include path
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

# enter subdirectories
add_subdirectory(tasty_int)
