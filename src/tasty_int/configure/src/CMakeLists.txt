set(target generate_tasty_int_token_values_file)

set(
    sources
    ${target}.cpp
)

add_executable(${target} ${sources})

foreach(library ${TASTY_INT_STATIC_LIBRARY} ${TASTY_INT_SHARED_LIBRARY})
    if(TARGET ${library})
        message(STATUS "${library} IS a target")
    else()
        message(STATUS "${library} IS NOT a target")
    endif()

    add_custom_command(
        TARGET  ${library}
        PRE_LINK
        COMMAND ${target} ${TASTY_INT_TOKEN_VALUES_FILE}
        COMMENT "generate TastyInt 'token_values' lookup tables"
    )
endforeach()

# add_custom_command(
#     OUTPUT  ${TASTY_INT_TOKEN_VALUES_FILE}
#     COMMAND ${target} ${TASTY_INT_TOKEN_VALUES_FILE}
# )
