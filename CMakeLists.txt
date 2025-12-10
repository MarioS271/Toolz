cmake_minimum_required(VERSION 3.20)
project(Toolz_WinAPI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC src/*.cpp src/app/*.cpp)
add_executable(toolz ${SRC})

target_include_directories(toolz PRIVATE ${CMAKE_SOURCE_DIR}/include)