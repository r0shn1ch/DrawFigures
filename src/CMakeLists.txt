find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_library(libGeometry STATIC
    Shader.cpp
    ShapeRenderer.cpp
)
target_include_directories(libGeometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(libGeometry PUBLIC
    glfw
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glm::glm
)

add_executable(DrawFiguresApp main.cpp)
target_link_libraries(DrawFiguresApp PRIVATE libGeometry)
