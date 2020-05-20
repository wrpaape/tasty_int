if(PROJECT_CMAKE_STD_FILESYSTEM_LIBRARY_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_STD_FILESYSTEM_LIBRARY_INCLUDED TRUE)
#[=======================================================================[.rst:
std_filesystem_library
----------------------

Using the C++17 std::filesystem library may require additional compiler/linker
options.  This Module defines ``STD_FILESYSTEM_LIBRARY``, which, if present, is
required linkage for targets that use the std::filesystem library.  Typical
usage:

::

    include(std_filesystem_library)
    add_executable(my_exec my_exec.cpp) # uses std::filesystem
    if(STD_FILESYSTEM_LIBRARY)
        target_link_libraries(my_exec ${STD_FILESYSTEM_LIBRARY})
    endif()

#]=======================================================================]
function(set_std_filesystem_library)
    set(binary_dir ${PROJECT_CMAKE_BINARY_DIR}/std_filesystem_library)
    set(src_dir    ${PROJECT_CMAKE_SRC_DIR}/std_filesystem_library)
    set(library_candidates "" "stdc++fs" "c++fs")
    foreach(library IN LISTS library_candidates)
        try_compile(
            library_compiled
            ${binary_dir}
            ${src_dir}/test_std_filesystem_library.cpp
            LINK_LIBRARIES ${library}
        )

        if(library_compiled)
            set(supported_library ${library})
            break()
        endif()
    endforeach()

    if(library_compiled)
        if(NOT supported_library)
            set(found_library "<NONE REQUIRED>")
        else()
            set(found_library "-l${supported_library}")
        endif()
        message(
            STATUS
            "Found the std::filesystem library: ${found_library}."
            )
    else()
        message(
            FATAL_ERROR
            "Failed to find the std::filesytem library.  "
            "Tried these candidates '${library_candidates}'."
            )
    endif()

    set(STD_FILESYSTEM_LIBRARY "${supported_library}" PARENT_SCOPE)
endfunction()

set_std_filesystem_library()
