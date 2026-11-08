cmake_minimum_required(VERSION 3.22)
project(tlf CXX)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(SDL3 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG release-3.2.10 GIT_SHALLOW TRUE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)
add_library(last_engine STATIC
  ${CMAKE_CURRENT_LIST_DIR}/../../../../../engine/core/SaveSystem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/../../../../../engine/world/Level.cpp
  ${CMAKE_CURRENT_LIST_DIR}/../../../../../engine/audio/AudioStub.cpp
  ${CMAKE_CURRENT_LIST_DIR}/../../../../../engine/renderer/PS1Renderer.cpp)
target_include_directories(last_engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../../../../engine)
add_library(main SHARED ${CMAKE_CURRENT_LIST_DIR}/../../../../../platform/sdl/main.cpp)
target_link_libraries(main PRIVATE last_engine SDL3::SDL3 log EGL GLESv2 android)
