add_executable(server
    src/Main.cpp
    ${PROJECT_SOURCE_DIR}/libs/game/src/stdafx.cpp
)

if(MSVC)
    target_compile_definitions(server PRIVATE
        "$<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>"
        "$<$<CONFIG:Debug>:_HAS_ITERATOR_DEBUGGING=0>"
    )
    target_link_options(server PRIVATE
        "/SUBSYSTEM:WINDOWS"
        "/ENTRY:wWinMainCRTStartup"
    )
else()
    target_link_libraries(server PRIVATE -static-libstdc++ -no-pie)
endif()

target_link_libraries(server PRIVATE GameCore GameLib)

# copy *.pak next to the binary
file(COPY ${PROJECT_SOURCE_DIR}/assets/Project.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
file(COPY ${PROJECT_SOURCE_DIR}/assets/Engine.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
