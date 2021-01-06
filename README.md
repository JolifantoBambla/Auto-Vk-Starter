# Auto-Vk-Starter
![Build (GCC/Clang/MSVC)](https://github.com/lHerzberger/Auto-Vk-Starter/workflows/Build%20(GCC/Clang/MSVC)/badge.svg)

A template for projects using the [Auto-Vk](https://github.com/cg-tuwien/Auto-Vk) library.

## Setup

### Use this template
Click on the [Button](https://github.com/lHerzberger/Auto-Vk-Starter/generate) near the top of the page to generate your own project using this template.
Then simply clone your newly created project.

### Install dependencies
* A [Vulkan 1.1 SDK](https://vulkan.lunarg.com/sdk/home) or newer
* A C++20 compiler
* [CMake 3.14](https://cmake.org/) or newer

## Build & Run

### Linux
Within the directory to which you cloned your project and run the following commands:
```
mkdir build
cd build
cmake .. && make
./Auto-Vk-Starter
```

### Windows/Visual Studio 2019
Make sure you have installed [CMake tools for Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160#installation).

Open the directory which contains your project with Visual Studio, wait for Visual Studio to run the `CMake` configuration and then select `Auto_Vk_Starter.exe`/`<Your Project Name>.exe` as `Startup Item` and run it by pressing the "play" button.

## Found a bug?
If you found a bug in the template (i.e. in the provided `src/main.cpp`, the `CMake` or GitHub workflow files) please open an issue directly in the template project.

However, if the bug you found is in [Auto-Vk](https://github.com/cg-tuwien/Auto-Vk), please create the issue directly over there.

## See also
* [Auto-Vk](https://github.com/cg-tuwien/Auto-Vk): A low-level convenience and productivity layer atop [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp).
* [Gears-Vk](https://github.com/cg-tuwien/Gears-Vk): A larger real-time rendering framework built on top of [Auto-Vk](https://github.com/cg-tuwien/Auto-Vk).
