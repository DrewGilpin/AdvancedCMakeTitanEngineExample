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
    GIT_TAG v1.14.1
)
set(SPDLOG_ENABLE_PCH OFF  CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

enable_testing()

add_executable(UnitTests
    MyClassTests.cpp
    SpdlogTest.cpp
    EE_boot_stubs.cpp
    ${PROJECT_SOURCE_DIR}/libs/game/src/stdafx.cpp
)

target_compile_definitions(UnitTests PRIVATE FMT_USE_FCNTL=0 SPDLOG_FORCE_COLOR=1)

target_link_libraries(UnitTests PRIVATE gtest_main spdlog::spdlog_header_only GameCore GameLib)

if(NOT MSVC)
    target_link_options(UnitTests PRIVATE -Wl,--allow-multiple-definition)
endif()

include(GoogleTest)
gtest_discover_tests(UnitTests WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} DISCOVERY_TIMEOUT 30)

# copy required engine assets next to the test executable
file(COPY ${PROJECT_SOURCE_DIR}/assets/Project.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets/Engine.pak
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
