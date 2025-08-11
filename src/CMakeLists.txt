cmake_minimum_required(VERSION 3.15)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(DrawFigures
    main.cpp
    Renderer.cpp
    Shader.cpp
    IShape.h
)

target_include_directories(DrawFigures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DrawFigures PRIVATE
    glfw
    GLEW::GLEW
    ${OPENGL_LIBRARIES}
    glm::glm
)
