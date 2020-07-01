# MIT License
# 
# Copyright (c) 2019 Cristian Adam
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#[=======================================================================[.rst:
bundle_static_library
---------------------

This Module defines bundle_static_library():

::

    bundle_static_library(<bundled_tgt_name> [<static_lib>...])

which adds a new imported STATIC library, <bundled_tgt_name>, by bundling the
provided list of STATIC libraries.
#]=======================================================================]
function(bundle_static_library bundled_tgt_name)
  set(static_libs ${ARGN})
  if(NOT static_libs)
    message(
      FATAL_ERROR
      "bundle_static_library() - No static libraries provided for "
      "${bundled_tgt_name}; aborting."
    )
  endif()

  function(_recursively_collect_dependencies input_target)
    get_target_property(_input_interface_include_dirs
                        ${input_target}
                        INTERFACE_INCLUDE_DIRECTORIES)
    list(APPEND interface_include_dirs)
    set(_input_link_libraries LINK_LIBRARIES)
    get_target_property(_input_type ${input_target} TYPE)
    if (${_input_type} STREQUAL "INTERFACE_LIBRARY")
      set(_input_link_libraries INTERFACE_LINK_LIBRARIES)
    endif()
    get_target_property(public_dependencies ${input_target} ${_input_link_libraries})
    foreach(dependency IN LISTS public_dependencies)
      if(TARGET ${dependency})
        get_target_property(alias ${dependency} ALIASED_TARGET)
        if (TARGET ${alias})
          set(dependency ${alias})
        endif()
        get_target_property(_type ${dependency} TYPE)
        if (${_type} STREQUAL "STATIC_LIBRARY")
          list(APPEND static_libs ${dependency})
        endif()

        get_property(library_already_added
          GLOBAL PROPERTY _${bundled_tgt_name}_static_bundle_${dependency})
        if (NOT library_already_added)
          set_property(GLOBAL PROPERTY _${bundled_tgt_name}_static_bundle_${dependency} ON)
          _recursively_collect_dependencies(${dependency})
        endif()
      endif()
    endforeach()
    set(static_libs ${static_libs} PARENT_SCOPE)
    set(interface_include_dirs ${interface_include_dirs} PARENT_SCOPE)
  endfunction()

  foreach(static_lib ${static_libs}) 
      _recursively_collect_dependencies(${static_lib})
  endforeach()
  list(REMOVE_DUPLICATES static_libs)

  set(bundled_tgt_full_name 
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${bundled_tgt_name}${CMAKE_STATIC_LIBRARY_SUFFIX})

  if (CMAKE_CXX_COMPILER_ID MATCHES "^(Clang|GNU)$")
    set(obj_dir ${CMAKE_CURRENT_BINARY_DIR}/${bundled_tgt_name}-objects)
    file(MAKE_DIRECTORY ${obj_dir})

    set(ar_tool ${CMAKE_AR})
    if (CMAKE_INTERPROCEDURAL_OPTIMIZATION)
      set(ar_tool ${CMAKE_CXX_COMPILER_AR})
    endif()

    set(unpack_static_libs)
    set(tgt_obj_globs)
    foreach(tgt IN LISTS static_libs)
      set(tgt_obj_dir ${obj_dir}/${tgt})
      add_custom_target(
        unpack-${tgt}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${tgt_obj_dir}
        COMMAND ${CMAKE_COMMAND} -E make_directory   ${tgt_obj_dir}
        COMMAND ${CMAKE_COMMAND} -E chdir ${tgt_obj_dir} ${ar_tool} -x $<TARGET_FILE:${tgt}>
        COMMENT "Unpacking ${tgt}"
        VERBATIM)
      list(APPEND unpack_static_libs unpack-${tgt})
      list(APPEND tgt_obj_globs ${tgt_obj_dir}/*${CMAKE_CXX_OUTPUT_EXTENSION})
    endforeach()

    add_custom_command(
      COMMAND ${ar_tool} -crs ${bundled_tgt_full_name} ${tgt_obj_globs}
      OUTPUT  ${bundled_tgt_full_name}
      DEPENDS ${unpack_static_libs}
      COMMENT "Bundling ${bundled_tgt_name}")
  elseif(MSVC)
    get_filename_component(bin_path ${CMAKE_LINKER} DIRECTORY)
    find_program(lib_tool lib PATHS ${bin_path})
    if(NOT lib_tool)
        message(FATAL_ERROR "Cannot find lib.exe; aborting.")
    endif()

    foreach(tgt IN LISTS static_libs)
      list(APPEND static_libs_full_names $<TARGET_FILE:${tgt}>)
    endforeach()

    add_custom_command(
      COMMAND ${lib_tool} /NOLOGO /OUT:${bundled_tgt_full_name} ${static_libs_full_names}
      OUTPUT ${bundled_tgt_full_name}
      DEPENDS ${static_libs}
      COMMENT "Bundling ${bundled_tgt_name}"
      VERBATIM)
  else()
    message(FATAL_ERROR "Unknown bundle scenario!")
  endif()

  add_custom_target(bundle-${bundled_tgt_name} ALL DEPENDS ${bundled_tgt_full_name})

  add_library(${bundled_tgt_name} STATIC IMPORTED)
  set_target_properties(${bundled_tgt_name} 
    PROPERTIES 
      IMPORTED_LOCATION ${bundled_tgt_full_name}
      INTERFACE_INCLUDE_DIRECTORIES "${interface_include_dirs}")
  add_dependencies(${bundled_tgt_name} bundle-${bundled_tgt_name})

endfunction()
