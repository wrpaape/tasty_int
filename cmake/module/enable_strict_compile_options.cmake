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
        set(options /W4 /WX)
    else()
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
    endif()
    string(REPLACE ";" " " space_separated_options "${options}")
    message(
        STATUS
        "Enabling the following strict compile options: "
        "'${space_separated_options}'."
    )
    add_compile_options(${options})
endfunction()
