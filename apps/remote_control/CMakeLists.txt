add_executable(remote_control
    src/main.cpp
    ${PROJECT_SOURCE_DIR}/libs/core/src/stdafx.cpp
)

target_link_libraries(remote_control PRIVATE game net core)

file(COPY ${PROJECT_SOURCE_DIR}/assets/
     DESTINATION $<TARGET_FILE_DIR:remote_control>)
