cmake_minimum_required(VERSION 3.28)
project(AdvancedCMakeTitanEngineExample LANGUAGES C CXX)

# Global compiler settings
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)

# Build subdirectories
add_subdirectory(libs/core)
add_subdirectory(libs/game)
add_subdirectory(apps/client)
add_subdirectory(apps/server)

# allow tests defined in subdirectories
enable_testing()
add_subdirectory(tests)
