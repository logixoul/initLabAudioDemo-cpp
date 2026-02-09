To clone:
    git clone --depth 1 --recurse-submodules --shallow-submodules https://github.com/logixoul/initLabAudioDemo-cpp.git

To build on Windows:
1. Install cmake (get "Windows x64 Installer" from https://cmake.org/download/)
2. Install "Build Tools for Visual Studio 2026" (https://aka.ms/vs/stable/vs_BuildTools.exe)
3. In the project root, run:
    mkdir msvc
    cd msvc
    cmake -G "Visual Studio 18 2026" ..

To setup VS Code for comfort:
- install these extensions:
    ms-vscode.cmake-tools
    ms-vscode.cpptools
