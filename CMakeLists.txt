cmake_minimum_required(VERSION 3.22)
project(TheLastOfFavelas CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(last_engine STATIC
  engine/core/SaveSystem.cpp
  engine/world/Level.cpp
  engine/audio/AudioStub.cpp
)
target_include_directories(last_engine PUBLIC engine)
# SDL3 (Android / desktop) via FetchContent — no system install needed
include(FetchContent)
FetchContent_Declare(SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.10
  GIT_SHALLOW TRUE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)
add_executable(the_last_of_favelas platform/sdl/main.cpp)
target_link_libraries(the_last_of_favelas PRIVATE last_engine SDL3::SDL3)
if(ANDROID)
  target_link_libraries(the_last_of_favelas PRIVATE log EGL GLESv2 android)
endif()
if(NOT ANDROID)
  target_link_libraries(the_last_of_favelas PRIVATE EGL GLESv2)
endif()
