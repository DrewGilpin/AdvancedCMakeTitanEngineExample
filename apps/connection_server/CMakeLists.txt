add_executable(connection_server
    src/main.cpp
    ${PROJECT_SOURCE_DIR}/libs/core/src/stdafx.cpp
)

target_link_libraries(connection_server PRIVATE game net core)

file(COPY ${PROJECT_SOURCE_DIR}/assets/
     DESTINATION $<TARGET_FILE_DIR:connection_server>)
