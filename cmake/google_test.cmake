# Google Test Testing Framework
# ------------------------------------------------------------------------------
find_package(GTest)
if(NOT GTEST_FOUND)
    # We need thread support
    find_package(Threads REQUIRED)

    # Enable ExternalProject CMake module
    include(ExternalProject)

    # Download and install GoogleTest
    ExternalProject_Add(
        gtest
        PREFIX          ${PROJECT_TEST_SRC_DIR}/gtest
        URL             https://github.com/google/googletest/archive/master.zip
        INSTALL_COMMAND "" # Disable install step
    )

    # Get GTest source and binary directories from CMake project
    ExternalProject_Get_Property(gtest SOURCE_DIR BINARY_DIR)

    # Create a libgtest target to be used as a dependency by test programs
    add_library(libgtest IMPORTED STATIC GLOBAL)
    add_dependencies(libgtest gtest)

    # Set libgtest properties
    file(GLOB LIBGTEST_LOCATION ${BINARY_DIR}/googlemock/gtest/libgtest*)
    set_target_properties(libgtest PROPERTIES
        IMPORTED_LOCATION                 ${LIBGTEST_LOCATION}
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
    )

    # Create a libgmock target to be used as a dependency by test programs
    add_library(libgmock IMPORTED STATIC GLOBAL)
    add_dependencies(libgmock gtest)

    # Set libgmock properties
    file(GLOB LIBGMOCK_LOCATION ${BINARY_DIR}/googlemock/libgmock*)
    set_target_properties(libgmock PROPERTIES
        IMPORTED_LOCATION                 ${LIBGMOCK_LOCATION}
        IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
    )

    # I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
    set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/googletest/include)
    set(GMOCK_INCLUDE_DIRS ${SOURCE_DIR}/googlemock/include)
endif()


function(add_gtest)
endfunction(add_gtest)
