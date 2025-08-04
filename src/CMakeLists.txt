find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_library(geometry
    Shader.cpp
    ShapeRenderer.cpp
)

target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(geometry PUBLIC
    glfw
    GLEW::GLEW
    ${OPENGL_LIBRARIES}
    glm::glm
)
add_executable(GeometryApp main.cpp)
target_link_libraries(GeometryApp PRIVATE geometry)
