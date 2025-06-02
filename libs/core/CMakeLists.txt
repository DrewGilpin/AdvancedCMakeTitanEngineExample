add_library(GameCore INTERFACE)

# Include directories for engine and third-party headers
# third_party/enet is header-only and Esenthel headers are treated as SYSTEM

target_include_directories(GameCore INTERFACE
    ${PROJECT_SOURCE_DIR}/third_party/enet
)

target_include_directories(GameCore SYSTEM INTERFACE
    ${PROJECT_SOURCE_DIR}/third_party/EE
)

# Platform specific compile options
if(MSVC)
    target_compile_definitions(GameCore INTERFACE _WIN64 _CRT_SECURE_NO_WARNINGS)
    target_compile_options(GameCore INTERFACE /MP /permissive- /Zc:twoPhase- /EHsc /utf-8)
else()
    target_compile_definitions(GameCore INTERFACE __linux__)
    target_compile_options(GameCore INTERFACE
        -fms-extensions -fno-pic -fno-pie
        -fshort-wchar -fpermissive
        -ffast-math -ffriend-injection
    )
    target_link_options(GameCore INTERFACE -no-pie)
endif()
