cmake_minimum_required(VERSION 3.28)
project(QuestForTerritory LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/core)
add_subdirectory(libs/net)
add_subdirectory(libs/game)

add_subdirectory(apps/client)
add_subdirectory(apps/connection_server)
add_subdirectory(apps/database_server)
add_subdirectory(apps/physics_server)
add_subdirectory(apps/world_server)
add_subdirectory(apps/remote_control)

add_subdirectory(tests)
