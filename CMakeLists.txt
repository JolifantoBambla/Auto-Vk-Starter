cmake_minimum_required(VERSION 3.14)
project(Auto_Vk_Starter)

set(CMAKE_CXX_STANDARD 23)

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
