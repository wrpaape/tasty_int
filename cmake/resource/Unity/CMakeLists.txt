cmake_minimum_required(VERSION 3.0)

project(
    Unity
    VERSION 0.1.0
    LANGUAGES C
)

include(CTest)   # sets BUILD_TESTING
enable_testing() # add 'make test' to run unit tests

add_test(
    NAME              test_unity_testing_framework
    COMMAND           ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/test
)

# cmake options
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD       11)

file(GLOB_RECURSE sources src/*.c)
file(GLOB_RECURSE headers src/*.h)
file(GLOB_RECURSE scripts auto/*)

add_library(unity SHARED ${sources} ${headers})

target_compile_definitions(
    unity
    INTERFACE -DUNITY_INCLUDE_CONFIG_H
)

install(
    TARGETS     unity
    DESTINATION lib
)
install(
    FILES       ${headers}
    DESTINATION include/unity
)
install(
    FILES       ${scripts}
    DESTINATION script/Unity
)
