if(PROJECT_CMAKE_NAMESPACES_INCLUDED)
    return()
endif()
set(PROJECT_CMAKE_NAMESPACES_INCLUDED TRUE)
#[=======================================================================[.rst:
namespaces
----------
This Module defines ``concat_namespaces``

::

    concat_namespaces(<prev_namespace> <next_namespace> <result>)

which, if namespaces are supported:

::
    
    1. concatenates <prev_namespace> with <next_namespace>, and stores the
       result to <result>
    2. creates a ``CACHE`` variable ``<prev_namespace><next_namespace>-`` that
       evaluates to a ``STRING`` value equal to its name


and ``push_namespace``:

::

    push_namespace(<namespace>)


which, if namespaces are supported:

::

    1. concatenates variable ``CURRENT_NAMESPACE`` with <namespace>
    2. defines ``CURRENT_NAMESPACE`` to the result in the current scope

The purpose of this module is to allow platforms for which lengthy namespaces
(which yield lengthy binary paths) jeopardize the build to toggle them off.
#]=======================================================================]
# External API
# ------------------------------------------------------------------------------
function(concat_namespaces prev_namespace next_namespace result)
    if(NOT WIN32)
        string(JOIN "-" ${result} ${prev_namespace}${next_namespace} "")

        set(${${result}} ${${result}} CACHE STRING
            "A namespace that expands for supported build environments.")

        set(${result} ${${result}} PARENT_SCOPE)
    endif()
endfunction()

function(push_namespace next_namespace)
    concat_namespaces("${CURRENT_NAMESPACE}" ${next_namespace} CURRENT_NAMESPACE)

    set(CURRENT_NAMESPACE "${CURRENT_NAMESPACE}" PARENT_SCOPE)
endfunction()
