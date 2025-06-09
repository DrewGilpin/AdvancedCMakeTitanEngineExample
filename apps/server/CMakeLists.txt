add_executable(server
    src/Main.cpp
    src/ConnectionsToClients.cpp
    ${PROJECT_SOURCE_DIR}/libs/game/src/stdafx.cpp
)

include(FetchContent)
FetchContent_Declare(
    nats
    GIT_REPOSITORY https://github.com/nats-io/nats.c.git
    GIT_TAG v3.10.1
)
set(NATS_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(NATS_BUILD_STREAMING OFF CACHE INTERNAL "")
set(NATS_BUILD_WITH_TLS OFF CACHE INTERNAL "")
set(NATS_BUILD_LIB_SHARED OFF CACHE INTERNAL "")
set(NATS_BUILD_LIB_STATIC ON CACHE INTERNAL "")
set(BUILD_TESTING OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nats)

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

target_link_libraries(server PRIVATE GameCore GameLib nats_static)

# copy *.pak next to the binary
file(COPY ${PROJECT_SOURCE_DIR}/assets/Project.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
file(COPY ${PROJECT_SOURCE_DIR}/assets/Engine.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
