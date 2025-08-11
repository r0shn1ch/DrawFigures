cmake_minimum_required(VERSION 3.15)
project(DrawFigures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

target_sources(DrawFigures
  PRIVATE
    src/Renderer.h src/Renderer.cpp
    src/Shapes.h src/Shapes.cpp
    src/Shader.h src/Shader.cpp
)
