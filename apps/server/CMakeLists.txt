add_executable(server
    src/server_main.cpp
)

if(MSVC)
    target_compile_definitions(server PRIVATE
        "$<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>"
        "$<$<CONFIG:Debug>:_HAS_ITERATOR_DEBUGGING=0>"
    )
else()
    target_link_libraries(server PRIVATE -static-libstdc++ -nopie)
endif()

target_link_libraries(server PRIVATE GameCore)

