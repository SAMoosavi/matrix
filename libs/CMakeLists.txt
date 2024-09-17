
set(EXTERNAL_DEPENDENCIES
        googletest
)

foreach(DEPENDENCIES ${EXTERNAL_DEPENDENCIES})
    add_subdirectory(${DEPENDENCIES})
endforeach()
