foreach(base 36 64)
    add_google_test(
        NAME    value_from_base_${base}_token_test
        SOURCES value_from_base_${base}_token_test.cpp
                $<TARGET_OBJECTS:tasty_int-detail-value_from_base_${base}_token>
    )
endforeach()
