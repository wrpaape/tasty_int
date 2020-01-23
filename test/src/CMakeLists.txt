# test_third_party
# ------------------------------------------------------------------------------
include(add_third_party)
add_third_party(
    NAME "testing third party dependencies"
    INSTALL_PREFIX ${PROJECT_TEST_DIR}
)

# find artifacts
find_package(Threads REQUIRED) # CMAKE_THREAD_LIBS_INIT
foreach(library ${GOOGLE_TEST_LIBRARIES})
    add_library(${library} STATIC IMPORTED GLOBAL)
    set(filename
        ${CMAKE_STATIC_LIBRARY_PREFIX}${library}${CMAKE_DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
    set_target_properties(
        ${library}
        PROPERTIES
        IMPORTED_LOCATION                 ${PROJECT_TEST_LIB_DIR}/${filename}
        INTERFACE_INCLUDE_DIRECTORIES     ${PROJECT_TEST_INCLUDE_DIR}
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
    )
endforeach()
