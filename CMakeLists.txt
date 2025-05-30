cmake_minimum_required(VERSION 3.28)
project(BasicAppCmake LANGUAGES C CXX)

# ▸ make our objects use /MT or /MTd so they match Engine64DX11.lib
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
            "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)

# ────────────────────────────────────────────────────────────────
# 0.  Build-system glue – include-dirs & compile/link flags only
# ────────────────────────────────────────────────────────────────
add_library(GameCore INTERFACE)

target_include_directories(GameCore INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Source          # your own headers
        ${CMAKE_CURRENT_SOURCE_DIR}/Include         # third-party headers
)

target_include_directories(GameCore SYSTEM INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine          # Esenthel headers
)

# ▸ Platform-specific build flags
if (MSVC)                                               # Windows / MSVC
    target_compile_definitions(GameCore INTERFACE _WIN64 _CRT_SECURE_NO_WARNINGS)
    target_compile_options   (GameCore
            INTERFACE /MP /permissive- /Zc:twoPhase- /EHsc)
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
# 1.  Engine and system libraries, picked per-platform
# ────────────────────────────────────────────────────────────────
if (WIN32)
    ## ── Esenthel DX11 engine: choose .lib by configuration ───────────────
    set(LIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lib")

    add_library(EsenthelEngine STATIC IMPORTED GLOBAL)
    set_target_properties(EsenthelEngine PROPERTIES
            IMPORTED_CONFIGURATIONS "Debug;Release;RelWithDebInfo;MinSizeRel"
            IMPORTED_LOCATION_DEBUG          "${LIB_DIRECTORY}/EngineDebug64DX11.lib"
            IMPORTED_LOCATION_RELEASE        "${LIB_DIRECTORY}/Engine64DX11.lib"
            IMPORTED_LOCATION_RELWITHDEBINFO "${LIB_DIRECTORY}/Engine64DX11.lib"
            IMPORTED_LOCATION_MINSIZEREL     "${LIB_DIRECTORY}/Engine64DX11.lib"
    )
    set(ESENTHEL_ENGINE_LIB EsenthelEngine)

    # ENet static library for Windows
    add_library(enet STATIC IMPORTED GLOBAL)
    set_target_properties(enet PROPERTIES
            IMPORTED_LOCATION "${LIB_DIRECTORY}/enet64.lib")

    ## ── Full Windows-SDK + DirectX import-library set (matches old VS cfg) ─
    ##    x3daudio1_7.lib is created by the stub step in the GH workflow.
    set(SYS_LIBS
            d3d11 d3d12 d3dcompiler
            dinput8 dsound dxgi dxguid xinput9_1_0 xaudio2
            winmm wininet ws2_32 imm32 psapi rpcrt4 version iphlpapi secur32 setupapi
            dbghelp comsupp concrt mscms advapi32 user32 shell32 ole32 oleaut32 gdi32
            uuid winspool runtimeobject
    )
else()
    set(ESENTHEL_ENGINE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/Lib/Engine.a")
    add_library(enet STATIC IMPORTED GLOBAL)
    set_target_properties(enet PROPERTIES
            IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Lib/libenet.a")
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
if (MSVC)
    target_sources(GameLib PRIVATE Source/getopt_stub.cpp)
endif()

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
    # 1)  Link the tiny getopt stub so Engine64DX11.lib resolves getopt/optarg/optind
    #target_sources(BasicAppCmake PRIVATE Source/getopt_stub.cpp)

    # 2)  Iterator-debugging OFF in Debug so the CRT matches Esenthel’s /MTd build
    target_compile_definitions(BasicAppCmake PRIVATE
            "$<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>"
            "$<$<CONFIG:Debug>:_HAS_ITERATOR_DEBUGGING=0>")

    # 3)  Make it a GUI app and tell the CRT to start at wWinMain
    target_link_options(BasicAppCmake PRIVATE
            "/SUBSYSTEM:WINDOWS"
            "/ENTRY:wWinMainCRTStartup")

    target_link_libraries(BasicAppCmake PRIVATE GameCore GameLib enet)
else()
    target_link_libraries(BasicAppCmake PRIVATE
            GameCore GameLib enet
            -static-libstdc++ -nopie)
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
