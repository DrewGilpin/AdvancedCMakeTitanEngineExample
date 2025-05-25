cmake_minimum_required(VERSION 3.12)
project(BasicAppCmake LANGUAGES C CXX)

# ─────────────────────────────────────────────────────────────────────
# 0.  Global settings
# ─────────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(__linux__)

# ─────────────────────────────────────────────────────────────────────
# 1.  Build-system glue (include dirs & compile/link flags – no code)
# ─────────────────────────────────────────────────────────────────────
add_library(GameCore INTERFACE)

target_include_directories(GameCore INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}          # e.g. "stdafx.h"
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

target_compile_options(GameCore INTERFACE
        -fms-extensions
        -fno-pic -fno-pie
        -fshort-wchar -fpermissive
        -ffast-math -ffriend-injection
)

# one-time linker flags inherited by every consumer
target_link_options(GameCore INTERFACE -no-pie)

# ─────────────────────────────────────────────────────────────────────
# 2.  Game/utility code shared by exe & tests
# ─────────────────────────────────────────────────────────────────────
set(ESENTHEL_ENGINE_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Lib/EsenthelEngine.a)

# **all runtime libs Esenthel depends on – single source of truth**
set(SYS_LIBS
        pthread dl m
        X11 Xi Xinerama Xrandr Xmu Xcursor Xxf86vm rt
        GL          # OpenGL
        openal
        z
        odbc
        udev
)

add_library(GameLib STATIC
        Source/MyClass.cpp
        Source/Auto.cpp
        Source/Shared/Commands.cpp
        # …add further shared .cpp files here …
)

# GameLib drags in Esenthel *and* every system lib it needs.
# Any target that links GameLib (UnitTests, the game exe, tools, …)
# therefore gets a fully-resolved link line automatically.
target_link_libraries(GameLib PUBLIC
        GameCore
        ${ESENTHEL_ENGINE_LIB}
        ${SYS_LIBS}
)

# ─────────────────────────────────────────────────────────────────────
# 3.  The actual game executable
# ─────────────────────────────────────────────────────────────────────
add_executable(BasicAppCmake
        stdafx.cpp
        Source/Main.cpp             # the one & only  int main()
)

# no more gigantic link list here – GameLib already carries it
target_link_libraries(BasicAppCmake PRIVATE
        GameCore
        GameLib
        -static-libstdc++ -nopie
)

# copy game data next to the binary
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Project.pak
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Engine.pak
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)

# ─────────────────────────────────────────────────────────────────────
# 4.  GoogleTest (fetched once, reused everywhere)
# ─────────────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)   # harmless on Linux
FetchContent_MakeAvailable(googletest)

enable_testing()

# ─────────────────────────────────────────────────────────────────────
# 4½.  spdlog – header-only (no extra .cpp files!)
# ─────────────────────────────────────────────────────────────────────
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.14.1          # or a newer tag
)
# we only need the header-only part -> don’t build its examples or tests
set(SPDLOG_ENABLE_PCH OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

# ─────────────────────────────────────────────────────────────────────
# 5.  Unit-test executable
# ─────────────────────────────────────────────────────────────────────
add_executable(UnitTests
        tests/MyClassTests.cpp
        tests/SpdlogTest.cpp
        tests/EE_boot_stubs.cpp     # boot stubs for Esenthel
        stdafx.cpp                  # pull in engine headers if needed
)

target_compile_definitions(UnitTests PRIVATE
        FMT_USE_FCNTL=0             # avoid the LOCK_READ/WRITE clash
        SPDLOG_FORCE_COLOR=1        # always emit ANSI colours
)

target_link_libraries(UnitTests PRIVATE
        gtest_main                  # Google-Test runtime (with its own main)
        spdlog::spdlog_header_only  # header-only flavour
        GameCore
        GameLib
)

# allow gtest_main’s main() to win over the one in Application.o
target_link_options(UnitTests PRIVATE
        -Wl,--allow-multiple-definition
)

# --------------------------------------------------------------------
#  Register every TEST(..) with CTest
# --------------------------------------------------------------------
include(GoogleTest)             # helper that ships with CMake ≥3.10

gtest_discover_tests(UnitTests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DISCOVERY_TIMEOUT 30        # seconds (optional)
)

# (remove the old "add_test(NAME run-unit-tests …)" line – no longer needed)

