#include "Renderer.h"
#include "IShape.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Renderer& Renderer::instance() {
    static Renderer r;
    return r;
}

void Renderer::init(int width, int height) {
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    const char* vs = R"glsl(
        #version 330 core
        layout(location=0) in vec2 aPos;
        uniform mat4 uModel;
        void main(){ gl_Position = uModel * vec4(aPos, 0.0, 1.0); }
    )glsl";
    const char* fs = R"glsl(
        #version 330 core
        uniform vec3 uColor;
        out vec4 frag;
        void main(){ frag = vec4(uColor, 1.0); }
    )glsl";
    m_shader = new Shader(vs, fs);
}

Renderer::~Renderer() {
    for (auto &kv : m_vaos) glDeleteVertexArrays(1, &kv.second);
    if (!m_vbos.empty()) glDeleteBuffers((GLsizei)m_vbos.size(), m_vbos.data());
    delete m_shader;
}

GLuint Renderer::makeVAO(const std::vector<glm::vec2>& verts) {
    GLuint vao=0, vbo=0;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec2), verts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    m_vbos.push_back(vbo);
    return vao;
}

void Renderer::drawShape(const IShape* shape) {
    if (!m_shader) return;
    const auto& verts = shape->getVertices();
    if (verts.empty()) return;
    if (!m_vaos.count(shape)) m_vaos[shape] = makeVAO(verts);
    GLuint vao = m_vaos[shape];
    glBindVertexArray(vao);
    m_shader->use();
    glm::mat4 M(1.0f);
    M = glm::translate(M, glm::vec3(shape->getPosition(), 0.0f));
    M = glm::rotate(M, glm::radians(shape->getRotation()), glm::vec3(0,0,1));
    M = glm::scale(M, glm::vec3(shape->getScale(), 1.0f));
    m_shader->setMat4("uModel", &M[0][0]);
    auto c = shape->getColor();
    m_shader->setVec3("uColor", c.x, c.y, c.z);
    glDrawArrays(shape->getDrawMode(), 0, (GLsizei)verts.size());
    glBindVertexArray(0);
}

int Renderer::showAndRun(const IShape& shape, int w, int h, const char* title) {
    glfwInit();
    // if (!glfwInit()) {
    //     std::cerr << "GLFW init failed\n";
    //     return 1;
    // }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    GLFWwindow* win = glfwCreateWindow(w, h, title, nullptr, nullptr);
    //if (!win) { glfwTerminate(); return 1; }
    glfwMakeContextCurrent(win);
    glewExperimental = GL_TRUE;
    glewInit();
    // if (glewInit() != GLEW_OK) {
    //     std::cerr << "GLEW init failed\n";
    //     glfwDestroyWindow(win); glfwTerminate(); return 1;
    // }
    int fbw = w, fbh = h;
    glfwGetFramebufferSize(win, &fbw, &fbh);
    init(fbw, fbh);
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glClearColor(0.07f,0.07f,0.08f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawShape(&shape);
        glfwSwapBuffers(win);
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
