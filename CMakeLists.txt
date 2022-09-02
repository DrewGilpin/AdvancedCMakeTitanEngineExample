# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

project ("BasicAppCmake")
SET (CMAKE_C_COMPILER "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_GENERATOR_PLATFORM x64)
add_compile_definitions(__linux__)

add_executable (BasicAppCmake "stdafx.cpp" "stdafx.h" 
"Source/Main.cpp" "Source/Auto.cpp" "Source/Shared/Commands.cpp" "Source/Shared/Commands.h"
"Source/@@headers.h" "Source/@ClientInfo.h" "Source/Auto.h" "Source/Main.h")

set_property(TARGET BasicAppCmake PROPERTY CXX_STANDARD 17)
set_property(TARGET BasicAppCmake PROPERTY C_STANDARD 17)

target_compile_options(BasicAppCmake PUBLIC "-fms-extensions")
target_compile_options(BasicAppCmake PUBLIC "-fno-pic")
target_compile_options(BasicAppCmake PUBLIC "-fno-pie")
target_compile_options(BasicAppCmake PUBLIC "-fshort-wchar")
target_compile_options(BasicAppCmake PUBLIC "-fpermissive")
target_compile_options(BasicAppCmake PUBLIC "-ffast-math")
target_compile_options(BasicAppCmake PUBLIC "-ffriend-injection")


target_link_options(BasicAppCmake PUBLIC "-lpthread")
target_link_options(BasicAppCmake PUBLIC "-ldl")
target_link_options(BasicAppCmake PUBLIC "-lX11")
target_link_options(BasicAppCmake PUBLIC "-lXi")
target_link_options(BasicAppCmake PUBLIC "-lXinerama")
target_link_options(BasicAppCmake PUBLIC "-lXrandr")
target_link_options(BasicAppCmake PUBLIC "-lrt")
target_link_options(BasicAppCmake PUBLIC "-lXmu")
target_link_options(BasicAppCmake PUBLIC "-lGL")
target_link_options(BasicAppCmake PUBLIC "-lopenal")
target_link_options(BasicAppCmake PUBLIC "-lz")
target_link_options(BasicAppCmake PUBLIC "-lodbc")
target_link_options(BasicAppCmake PUBLIC "-ludev")
target_link_options(BasicAppCmake PUBLIC "-lXcursor")
target_link_options(BasicAppCmake PUBLIC "-lXxf86vm")
target_link_options(BasicAppCmake PUBLIC "-static-libstdc++")
target_link_options(BasicAppCmake PUBLIC "-nopie")

target_include_directories(BasicAppCmake PUBLIC "./")
target_include_directories(BasicAppCmake PUBLIC "./Engine")
target_link_libraries(BasicAppCmake ${CMAKE_SOURCE_DIR}/Lib/EsenthelEngine.a)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Project.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Engine.pak DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)