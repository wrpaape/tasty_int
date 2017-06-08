cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(
    Unity
    VERSION 0.1.0
    LANGUAGES C
)

include(CTest)   # sets BUILD_TESTING
enable_testing() # add 'make test' to run unit tests

# cmake options
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD       11)

file(GLOB sources src/*.c)
file(GLOB headers src/*.h)
file(GLOB scripts auto/*)

set(headers_install_dir   include/Unity)
set(scripts_install_dir   scripts/Unity)
set(libraries_install_dir lib)

add_library(unity_test SHARED ${sources} ${headers})

add_test(
    NAME              test_unity_test_framework
    COMMAND           $(MAKE) test
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/test
)

# install(DIRECTORY DESTINATION ${headers_install_dir})
# install(DIRECTORY DESTINATION ${scripts_install_dir})

install(TARGETS ${headers} DESTINATION ${headers_install_dir})
install(TARGETS ${scripts} DESTINATION ${scripts_install_dir})
install(TARGETS unity_test DESTINATION ${libraries_install_dir})
