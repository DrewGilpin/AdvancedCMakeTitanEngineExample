add_library(core INTERFACE)

# Include directories for engine and third-party headers
# Using BUILD_INTERFACE ensures correct paths when building the library

target_include_directories(core INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/core/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/enet>
)

target_include_directories(core SYSTEM INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/EE>
)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "" FORCE)
    target_compile_definitions(core INTERFACE _WIN64 _CRT_SECURE_NO_WARNINGS)
    target_compile_options(core INTERFACE /MP /permissive- /Zc:twoPhase- /EHsc)
else()
    target_compile_definitions(core INTERFACE __linux__)
    target_compile_options(core INTERFACE -fms-extensions -fno-pic -fno-pie
            -fshort-wchar -fpermissive -ffast-math -ffriend-injection)
    target_link_options(core INTERFACE -no-pie)
endif()
