cmake_minimum_required(VERSION 3.20)

project(initLabAudioDemo-cpp
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

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(initLabAudioDemo-cpp
    ${SOURCES}
)

target_link_libraries(initLabAudioDemo-cpp PRIVATE raylib)
target_link_libraries(initLabAudioDemo-cpp PRIVATE glfw)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(initLabAudioDemo-cpp PRIVATE ${RAYGUI_INCLUDE_DIRS})

# On some toolchains you may need these. Harmless if not.
if(APPLE)
    # raylib already links the needed frameworks in most cases,
    # but keeping this here can help when toolchains differ.
    target_compile_definitions(initLabAudioDemo-cpp PRIVATE PLATFORM_DESKTOP)
endif()

# Warnings (nice for teaching, but not overly strict)
if(MSVC)
    target_compile_options(initLabAudioDemo-cpp PRIVATE /W4)
else()
    target_compile_options(initLabAudioDemo-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
