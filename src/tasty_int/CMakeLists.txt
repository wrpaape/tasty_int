include(bundle_static_library)
include(namespaces)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


push_namespace(tasty_int)

# build internal implementation
add_subdirectory(detail)

# collect modules into single static library
bundle_static_library(
    tasty_int
    ${tasty_int-detail-}integer_comparison
    ${tasty_int-detail-}integer_addition
    ${tasty_int-detail-}integer_subtraction
    ${tasty_int-detail-}integer_multiplication
    ${tasty_int-detail-}integer_division
    ${tasty_int-detail-}integer_input
    ${tasty_int-detail-}integer_output
    ${tasty_int-detail-conversions-}integer_from_floating_point
    ${tasty_int-detail-conversions-}integer_from_signed_integral
    ${tasty_int-detail-conversions-}integer_from_unsigned_integral
    ${tasty_int-detail-conversions-}integer_from_string
    ${tasty_int-detail-conversions-}floating_point_from_integer
    ${tasty_int-detail-conversions-}signed_integral_from_integer
    ${tasty_int-detail-conversions-}unsigned_integral_from_integer
    ${tasty_int-detail-conversions-}string_from_integer
)

# build unit tests
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# install TastyInt::TastyInt
add_library(${CMAKE_PROJECT_NAME} INTERFACE)
set(tasty_int_libraries tasty_int)
if(BUILD_COVERAGE)
    list(APPEND tasty_int_libraries ${CMAKE_LIBRARIES_COVERAGE})
endif()
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    INTERFACE
    ${tasty_int_libraries}
)
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    INTERFACE 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(
    ${CMAKE_PROJECT_NAME}
    INTERFACE
    cxx_std_20
)
find_enable_cpp_concepts_compile_options(enable_cpp_concepts_compile_options)
if(enable_cpp_concepts_compile_options)
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        INTERFACE
        ${enable_cpp_concepts_compile_options}
    )
endif()

set(tasty_int_cmake_files_install_dir
    "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}")
set(tasty_int_version_file
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake")
set(tasty_int_config_file
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake")
write_basic_package_version_file(
    ${tasty_int_version_file}
    VERSION       ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
get_target_property(TASTY_INT_INTERPROCEDURAL_OPTIMIZATION
                    tasty_int
                    INTERPROCEDURAL_OPTIMIZATION)
if(NOT TASTY_INT_INTERPROCEDURAL_OPTIMIZATION)
    set(TASTY_INT_INTERPROCEDURAL_OPTIMIZATION OFF)
endif()
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${CMAKE_PROJECT_NAME}Config.cmake.in
    ${tasty_int_config_file}
    INSTALL_DESTINATION ${tasty_int_cmake_files_install_dir}
    PATH_VARS           CMAKE_INSTALL_LIBDIR
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

set(tasty_int_targets_name ${CMAKE_PROJECT_NAME}Targets)
install(
    TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT  ${tasty_int_targets_name}
)
install(
    EXPORT      ${tasty_int_targets_name}
    NAMESPACE   ${CMAKE_PROJECT_NAME}::
    DESTINATION ${tasty_int_cmake_files_install_dir}
)
install(
    FILES       $<TARGET_LINKER_FILE:tasty_int>
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
    DIRECTORY   ${PROJECT_INCLUDE_DIR}/tasty_int
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES       ${tasty_int_version_file} ${tasty_int_config_file}
    DESTINATION ${tasty_int_cmake_files_install_dir}
)
