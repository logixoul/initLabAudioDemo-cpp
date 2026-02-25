To build on Windows 11 (with WSL):
1. Run:
    wsl --install Ubuntu
2. Reboot.
3. Start menu -> Ubuntu -> Run the following:
    sudo add-apt-repository ppa:xmake-io/xmake
    sudo apt update
    sudo apt install xmake

    sudo apt install build-essential
    # for glfw:
    sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libwayland-dev libxkbcommon-dev
    
5. Run:
    xmake build


To setup VS Code for comfort:
- install these extensions:
    ms-vscode-remote.remote-wsl   <--- if you're on Windows (WSL)
    ms-vscode.cpptools
    # no need for the xmake extension, it's buggy and slow
- then restart VSCode. It will prompt you to "Reopen in WSL" - click that.
- You can now run the app via Ctrl+Shift+B