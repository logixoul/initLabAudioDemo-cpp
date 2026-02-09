cmake_minimum_required(VERSION 3.20)

project(audio_course
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Good default for single-config generators (Ninja/Make).
# Multi-config generators (Visual Studio) ignore this.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Export compile_commands.json for VS Code / clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Raylib (vendored)
# -----------------------------
# raylib's CMakeLists.txt lives in its root.
# It produces a target named "raylib".
add_subdirectory(external/raylib)

# -----------------------------
# Your executable
# -----------------------------
add_executable(audio_course
    src/main.cpp
)

# raygui is usually just a header. If you keep it at external/raygui/raygui.h:
target_include_directories(audio_course PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/raygui
)

target_link_libraries(audio_course PRIVATE raylib)

# On some toolchains you may need these. Harmless if not.
if(APPLE)
    # raylib already links the needed frameworks in most cases,
    # but keeping this here can help when toolchains differ.
    target_compile_definitions(audio_course PRIVATE PLATFORM_DESKTOP)
endif()

# Warnings (nice for teaching, but not overly strict)
if(MSVC)
    target_compile_options(audio_course PRIVATE /W4)
else()
    target_compile_options(audio_course PRIVATE -Wall -Wextra -Wpedantic)
endif()
