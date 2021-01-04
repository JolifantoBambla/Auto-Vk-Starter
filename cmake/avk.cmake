cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    avk
    GIT_REPOSITORY      https://github.com/cg-tuwien/Auto-Vk.git
    GIT_TAG             master
)

FetchContent_MakeAvailable(avk)
