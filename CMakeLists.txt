# CMakeList.txt : CMake project for Vulkan-CMake-Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Vulkan-CMake-Template")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(VulkanHeaders CONFIG)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

add_library(MyVulkanLib STATIC  "src/Renderer.cpp"  "include/public/Vertex.h" )

target_include_directories(MyVulkanLib PUBLIC include/private)
target_include_directories(MyVulkanLib PUBLIC include/dep)
target_include_directories(MyVulkanLib PUBLIC include/public)

target_precompile_headers(MyVulkanLib PUBLIC include/private/pch.h)

target_link_libraries(MyVulkanLib PUBLIC glfw)
target_link_libraries(MyVulkanLib PUBLIC Vulkan::Vulkan)
target_link_libraries(MyVulkanLib PUBLIC glm::glm)
target_link_libraries(MyVulkanLib PUBLIC imgui::imgui)
target_link_libraries(MyVulkanLib PUBLIC assimp::assimp)
target_link_libraries(MyVulkanLib PUBLIC Vulkan::Headers GPUOpen::VulkanMemoryAllocator)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MyVulkanLib PROPERTY CXX_STANDARD 20)
endif()


add_executable (Vulkan-CMake-Template "example/main.cpp")
target_link_libraries(Vulkan-CMake-Template PRIVATE MyVulkanLib)