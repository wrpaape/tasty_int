if(PROJECT_CMAKE_ENABLE_STRICT_COMPILE_OPTIONS)
    return()
endif()
set(PROJECT_CMAKE_ENABLE_STRICT_COMPILE_OPTIONS TRUE)
#[=======================================================================[.rst:
enable_strict_compile_options
-------------------

This Module defines ``enable_strict_compile_options``, which applies "stricter"
constraints to the compile options in the current scope.  Typical usage:

::

    include(enable_strict_compile_options)
    enable_strict_compile_options()

#]=======================================================================]
function(enable_strict_compile_options)
    unset(supported_flags)
    if(MSVC)
        if(CMAKE_VERSION VERSION_LESS 3.15)
            # /W3 flag removed from default CMAKE_CXX_FLAGS in version 3.15
            # if left as is, appending '/W4' will generate a warning:
            #     Command line warning D9025 : overriding '/W3' with '/W4
            string(REGEX REPLACE "/W[0-4]" ""
                   CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING
                "Flags used by the CXX compiler during all build types.")
        endif()
        # @todo: TODO: reenable after resolving warnings
        # set(options /W4 /WX)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(options -W -Wall -Werror)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(
            options
            -Wall -Wextra -pedantic -Wstrict-aliasing -Wunreachable-code
            -Wcast-align -Wcast-qual -Wctor-dtor-privacy
            -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op
            -Wmissing-include-dirs -Wnoexcept -Wold-style-cast
            -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo
            -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef
            -Wno-unused -Wno-variadic-macros -Wno-parentheses
            -fdiagnostics-show-option -Werror
        )
    else()
        message(STATUS "Unknown compiler - not adding strict compile options.")
        return()
    endif()
    string(REPLACE ";" " " space_separated_options "${options}")
    message(
        STATUS
        "Enabling the following strict compile options: "
        "'${space_separated_options}'."
    )
    add_compile_options(${options})
endfunction()
