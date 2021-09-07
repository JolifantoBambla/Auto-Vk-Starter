cmake_minimum_required(VERSION 3.14)
project(Auto_Vk_Starter)

if (MSVC)
    # <ranges> support requires /std:c++latest on MSVC
    set(CMAKE_CXX_STANDARD 23)
else (MSVC)
    set(CMAKE_CXX_STANDARD 20)
endif (MSVC)

option(avkStarter_UseVMA "Use Vulkan Memory Allocator (VMA) for custom memory allocation." OFF)
if (${avkStarter_UseVMA})
    add_compile_definitions(AVK_USE_VMA)
endif()

add_executable(Auto_Vk_Starter src/main.cpp)

# Auto-Vk
set(avk_UseVMA ${avkStarter_UseVMA})
include(cmake/avk.cmake)
target_link_libraries(${PROJECT_NAME} PUBLIC avk)

# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
