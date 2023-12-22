# Mesmerize-Renderer

Mesmerize Renderer is a mid-low level Renderer API built on top of Vulkan, but I may add support for more backends like DirectX 12 or WEBGPU in the future. This was made as a way for me to streamline the process of setting up rendering for future projects.

## Required Packages
- GLM
- GLFW
- Vulkan
- Assimp
- Vulkan Memory Allocator

## Install
You can build the library using CMake.

if you are using CMake then you can add this to your CMake by downloading this project or using git submodules and and this to your CMake

```
add_subdirectory(MesmerizeRenderer)

...

...

target_link_libraries(MyApp PRIVATE MesmerizeRenderer)
```



## How to Use
Example usage can found in the example folder in [main.cpp](https://github.com/brevin33/Mesmerize-Renderer/blob/main/example/main.cpp)
