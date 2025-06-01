add_executable(physics_server
    src/main.cpp
    ${PROJECT_SOURCE_DIR}/libs/core/src/stdafx.cpp
)

target_link_libraries(physics_server PRIVATE game net core)

file(COPY ${PROJECT_SOURCE_DIR}/assets/
     DESTINATION $<TARGET_FILE_DIR:physics_server>)
