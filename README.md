To build on Windows 11 (with WSL):
1. Run:
    wsl --install Ubuntu
2. Reboot.
3. Start menu -> Ubuntu -> Run the following:
    sudo apt install clang cmake ninja-build libc6-dev lld gdb
    sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config glfw # for glfw
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libwayland-dev libxkbcommon-dev
    cd ~
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg && ./bootstrap-vcpkg.sh
4. Put this into your ~/.bashrc:
    export VCPKG_ROOT=~/vcpkg
    export PATH=$VCPKG_ROOT:$PATH
5. Run:
    cmake --preset=vcpkg
    cmake --build build


To setup VS Code for comfort:
- install these extensions:
    ms-vscode-remote.remote-wsl   <--- if you're on Windows (WSL)
    ms-vscode.cmake-tools
    ms-vscode.cpptools
- then restart VSCode. It will prompt you to "Reopen in WSL" - click that.