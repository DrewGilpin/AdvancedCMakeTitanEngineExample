add_executable(world_server
    src/main.cpp
    src/WorldServer.cpp
    ${PROJECT_SOURCE_DIR}/libs/core/src/stdafx.cpp
)

target_link_libraries(world_server PRIVATE game net core)

file(COPY ${PROJECT_SOURCE_DIR}/assets/
     DESTINATION $<TARGET_FILE_DIR:world_server>)
