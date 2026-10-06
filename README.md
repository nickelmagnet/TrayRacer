# TrayRacer

A ray tracer in C++, built from scratch to understand how light, math and GPUs actually work. 🔦

Runs on Linux (developed in WSL2). Window + UI via GLFW and Dear ImGui, display through Vulkan.

## The plan

1. **CPU ray tracer** renders the image into a pixel buffer.
2. Pixels get uploaded to the GPU through **Vulkan** and shown in the window (with ImGui controls).
3. **Later:** move the tracing itself onto the GPU (Vulkan compute shader, plus a BVH).

## Status

- [x] Vulkan + GLFW + ImGui window running
- [ ] CPU ray tracer (spheres, materials, bounces)
- [ ] CPU pixels shown in window via Vulkan
- [ ] BVH
- [ ] GPU ray tracing (Vulkan compute)

## Build

Needs: `make`, a C++ compiler, GLFW, Vulkan SDK/headers.

Dependencies in `vendor/` are git submodules, so clone with:

```bash
git clone --recursive https://github.com/nickelmagnet/TrayRacer.git
cd TrayRacer
make
./bin/TrayRacerApp
```

If you already cloned without `--recursive`: `git submodule update --init --recursive`
