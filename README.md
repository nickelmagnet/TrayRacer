# TrayRacer

TrayRacer is a C++17 Vulkan and Dear ImGui desktop application using GLFW. Its framework code is in `src/TrayRacer`, and the app entry point is in `TrayRacerApp`.

## Build and run in WSL2

Use a WSL2 Ubuntu installation with WSLg enabled to display the application window on your Windows desktop. Vulkan must also be available inside WSL.

Install the compiler, Make, Vulkan, and GLFW X11 development dependencies:

```bash
sudo apt update
sudo apt install build-essential make libgl-dev libx11-dev libxrandr-dev \
  libxinerama-dev libxcursor-dev libxi-dev libxxf86vm-dev libvulkan-dev \
  mesa-vulkan-drivers vulkan-tools
```

From the repository root, build and run:

```bash
make -j"$(nproc)"
make run
```

The executable is `build/TrayRacer`. To start it directly, run `./build/TrayRacer`. To remove generated objects and the executable, run `make clean`.

The Makefile compiles the vendored GLFW Linux/X11 sources and the included ImGui sources directly. You do not need Premake, CMake, or Ninja for this build. The vendored libraries remain under `vendor/`.
