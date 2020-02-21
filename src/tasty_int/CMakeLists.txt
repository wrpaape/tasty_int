# static and shared libraries are output to root 'lib' directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIB_DIR})

# build internal implementation
add_subdirectory(detail)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
