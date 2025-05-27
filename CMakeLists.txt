cmake_minimum_required(VERSION 3.28)
project(BasicAppCmake LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# ────────────────────────────────────────────────────────────────
# 0.  Build-system glue – include-dirs & compile/link flags only
# ────────────────────────────────────────────────────────────────
add_library(GameCore INTERFACE)

target_include_directories(GameCore INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Source          # your own headers
)

target_include_directories(GameCore SYSTEM INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine          # Esenthel headers
)

# ▸ Platform-specific build flags
if (MSVC)                                               # Windows / MSVC
    target_compile_definitions(GameCore INTERFACE _WIN64 _CRT_SECURE_NO_WARNINGS)
    target_compile_options   (GameCore INTERFACE /MP /permissive- /EHsc)
    target_link_options      (GameCore INTERFACE /SUBSYSTEM:CONSOLE)
else()                                                   # Linux (was original)
    target_compile_definitions(GameCore INTERFACE __linux__)
    target_compile_options   (GameCore INTERFACE
            -fms-extensions -fno-pic -fno-pie
            -fshort-wchar -fpermissive
            -ffast-math -ffriend-injection
    )
    target_link_options      (GameCore INTERFACE -no-pie)
endif()

# ────────────────────────────────────────────────────────────────
# 1.  Game/utility code shared by exe & tests
# ────────────────────────────────────────────────────────────────
if (WIN32)
    # create an imported library target whose .lib depends on the build type
    add_library(EsenthelEngine STATIC IMPORTED GLOBAL)

    set_target_properties(EsenthelEngine PROPERTIES
            # Release build → Engine64DX11.lib
            IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Lib/Engine64DX11.lib"
            # Debug   build → EngineDebug64DX11.lib
            IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/Lib/EngineDebug64DX11.lib"
    )

    set(ESENTHEL_ENGINE_LIB EsenthelEngine)
    set(SYS_LIBS winmm ws2_32)       # minimal Windows runtime libs
else()
    set(ESENTHEL_ENGINE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/Lib/EsenthelEngine.a")
    set(SYS_LIBS                                     # original Linux set
            pthread dl m X11 Xi Xinerama Xrandr Xmu Xcursor Xxf86vm rt
            GL openal z odbc udev
    )
endif()


add_library(GameLib STATIC
        Source/MyClass.cpp
        Source/Auto.cpp
        Source/Shared/Commands.cpp
)

target_link_libraries(GameLib PUBLIC
        GameCore
        ${ESENTHEL_ENGINE_LIB}
        ${SYS_LIBS}
)

# ────────────────────────────────────────────────────────────────
# 2.  The actual game executable
# ────────────────────────────────────────────────────────────────
add_executable(BasicAppCmake
        stdafx.cpp
        Source/Main.cpp
)

if (MSVC)
    target_link_libraries(BasicAppCmake PRIVATE GameCore GameLib)
else()
    target_link_libraries(BasicAppCmake PRIVATE
            GameCore GameLib
            -static-libstdc++ -nopie           # keeps the original behaviour
    )
endif()

# copy *.pak next to the binary (same for all OSes)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Project.pak
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Engine.pak
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)

# ────────────────────────────────────────────────────────────────
# 3.  Google-Test & spdlog (unchanged)
# ────────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.14.1
)
set(SPDLOG_ENABLE_PCH OFF  CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

enable_testing()

add_executable(UnitTests
        tests/MyClassTests.cpp
        tests/SpdlogTest.cpp
        tests/EE_boot_stubs.cpp
        stdafx.cpp
)

target_compile_definitions(UnitTests PRIVATE FMT_USE_FCNTL=0 SPDLOG_FORCE_COLOR=1)
target_link_libraries(UnitTests PRIVATE gtest_main spdlog::spdlog_header_only GameCore GameLib)

if (NOT MSVC)
    target_link_options(UnitTests PRIVATE -Wl,--allow-multiple-definition)
endif()

include(GoogleTest)
gtest_discover_tests(UnitTests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} DISCOVERY_TIMEOUT 30)
