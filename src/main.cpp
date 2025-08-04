#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <numbers>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "ShapeRenderer.h"

// Коллбэк GLFW для вывода ошибок
void glfwErrorCallback(int code, const char* description) {
    std::cerr << "[GLFW] Error " << code << ": " << description << "\n";
}

// Вершинный шейдер (с проекцией и модельной матрицей)
static const char* vertexSrc = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
uniform mat4 uModel;
uniform mat4 uProjection;
void main() {
    gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
}
)glsl";

// Фрагментный шейдер
static const char* fragmentSrc = R"glsl(
#version 330 core
uniform vec3 uColor;
out vec4 fColor;
void main() {
    fColor = vec4(uColor, 1.0);
}
)glsl";

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cerr << "Ошибка: не удалось инициализировать GLFW\n";
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GeometryApp", nullptr, nullptr);
    if (!window) {
        std::cerr << "Ошибка: не удалось создать окно GLFW\n";
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    // Диагностика контекста
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* render = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    const GLubyte* glslver  = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "[OpenGL] Vendor:   " << (vendor   ? reinterpret_cast<const char*>(vendor)   : "Unknown") << "\n";
    std::cout << "[OpenGL] Renderer: " << (render ? reinterpret_cast<const char*>(render) : "Unknown") << "\n";
    std::cout << "[OpenGL] Version:  " << (version  ? reinterpret_cast<const char*>(version)  : "Unknown") << "\n";
    std::cout << "[GLSL]   Version:  " << (glslver  ? reinterpret_cast<const char*>(glslver)  : "Unknown") << "\n";

    GLint profileMask = 0;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);
    if (profileMask & GL_CONTEXT_CORE_PROFILE_BIT) {
        std::cout << "[GL] Core Profile\n";
    } else if (profileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) {
        std::cout << "[GL] Compatibility Profile\n";
    } else {
        std::cout << "[GL] Profile: Unknown\n";
    }


    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        std::cerr << "[GLEW] Warning: " << glewGetErrorString(glewErr) << "\n";
    }
    while (glGetError() != GL_NO_ERROR) {}

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader(vertexSrc, fragmentSrc);
    ShapeRenderer renderer;

    GLsizei sqCnt, rectCnt, circCnt, ellCnt, hexCnt;
    GLuint sqVAO   = renderer.makeSquareVAO(sqCnt);                   // 60x60
    GLuint rectVAO = renderer.makeRectangleVAO(rectCnt, 100.0f, 50.0f); // 100x50
    GLuint circVAO = renderer.makeEllipseVAO(64, circCnt);            // 60x60
    GLuint ellVAO  = renderer.makeEllipseVAO(32, ellCnt);             // 100x40

    std::vector<glm::vec2> hexPts(7);
    hexPts[0] = {0.0f, 0.0f};
    constexpr float radius = 60.0f;
    constexpr float twoPi = std::numbers::pi_v<float> * 2.0f;
    for (int i = 0; i < 6; ++i) {
        float angle = twoPi * (float(i) / 6.0f);
        hexPts[i + 1] = { radius * std::cos(angle), radius * std::sin(angle) };
    }
    GLuint hexVAO = renderer.makePolygonVAO(hexPts, hexCnt); // ≈120x120

    glm::vec2 posSq   = {100, 500}, velSq   = {50, -40};
    glm::vec2 posRect = {600, 500}, velRect = {-40, -30};
    glm::vec2 posCirc = {100, 200}, velCirc = {70, 60};
    glm::vec2 posEll  = {600, 200}, velEll  = {-60, 70};
    glm::vec2 posHex  = {350, 100}, velHex  = {30, 55};

    float lastTime = glfwGetTime();
    int width = 800, height = 600;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        glfwGetFramebufferSize(window, &width, &height);
        glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height));

        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.id(), "uProjection"), 1, GL_FALSE, &projection[0][0]);

        auto update = [&](glm::vec2& pos, glm::vec2& vel, glm::vec2 size) {
            pos += vel * delta;
            if (pos.x < 0 || pos.x + size.x > width)  vel.x *= -1;
            if (pos.y < 0 || pos.y + size.y > height) vel.y *= -1;
        };
        update(posSq,   velSq,   {60, 60});
        update(posRect, velRect, {100, 50});
        update(posCirc, velCirc, {60, 60});
        update(posEll,  velEll,  {100, 40});
        update(posHex,  velHex,  {120, 120});

        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.drawVAO(sqVAO, sqCnt, posSq, 30.0f, {55.f, 55.f}, {1, 0, 0}, shader);
        renderer.drawVAO(rectVAO, rectCnt, posRect, -15.0f, {1, 1}, {0, 1, 0}, shader);
        renderer.drawVAO(circVAO, circCnt, posCirc, 0.0f, {55.f, 55.f}, {0, 0, 1}, shader);
        renderer.drawVAO(ellVAO, ellCnt, posEll, 45.0f, {55.f, 80.f}, {1, 1, 0}, shader);
        renderer.drawVAO(hexVAO, hexCnt, posHex, 0.0f, {1, 1}, {1, 0, 1}, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
