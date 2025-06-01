# Esenthel engine and system libraries
if(WIN32)
    set(LIB_DIRECTORY "${PROJECT_SOURCE_DIR}/third_party/EE")

    add_library(EsenthelEngine STATIC IMPORTED GLOBAL)
    set_target_properties(EsenthelEngine PROPERTIES
        IMPORTED_CONFIGURATIONS "Debug;Release;RelWithDebInfo;MinSizeRel"
        IMPORTED_LOCATION_DEBUG          "${LIB_DIRECTORY}/EngineDebug64DX11.lib"
        IMPORTED_LOCATION_RELEASE        "${LIB_DIRECTORY}/Engine64DX11.lib"
        IMPORTED_LOCATION_RELWITHDEBINFO "${LIB_DIRECTORY}/Engine64DX11.lib"
        IMPORTED_LOCATION_MINSIZEREL     "${LIB_DIRECTORY}/Engine64DX11.lib"
    )
    set(ESENTHEL_ENGINE_LIB EsenthelEngine)

    set(SYS_LIBS
        d3d11 d3d12 d3dcompiler
        dinput8 dsound dxgi dxguid xinput9_1_0 xaudio2
        winmm wininet ws2_32 imm32 psapi rpcrt4 version iphlpapi secur32 setupapi
        dbghelp comsupp concrt mscms advapi32 user32 shell32 ole32 oleaut32 gdi32
        uuid winspool runtimeobject
    )
else()
    set(ESENTHEL_ENGINE_LIB "${PROJECT_SOURCE_DIR}/third_party/EE/Engine.a")
    set(SYS_LIBS
        pthread dl m X11 Xi Xinerama Xrandr Xmu Xcursor Xxf86vm rt
        GL openal z odbc udev
    )
endif()

add_library(GameLib STATIC
    src/MyClass.cpp
    src/Auto.cpp
)

if(MSVC)
    target_sources(GameLib PRIVATE src/getopt_stub.cpp)
    target_compile_definitions(GameLib PRIVATE
        "$<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>"
        "$<$<CONFIG:Debug>:_HAS_ITERATOR_DEBUGGING=0>"
    )
endif()

target_include_directories(GameLib PUBLIC
    ${PROJECT_SOURCE_DIR}/libs/game/include
)

target_link_libraries(GameLib PUBLIC
    GameCore
    ${ESENTHEL_ENGINE_LIB}
    ${SYS_LIBS}
)
