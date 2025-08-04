#include "ShapeRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

ShapeRenderer::~ShapeRenderer() {
    for (auto& b : _buffers) {
        glDeleteVertexArrays(1, &b.vao);
        glDeleteBuffers     (1, &b.vbo);
    }
}

GLuint ShapeRenderer::makePolygonVAO(const std::vector<glm::vec2>& pts, GLsizei& outCount) {
    GLuint vao, vbo;
    glGenVertexArrays(1,&vao);
    glGenBuffers     (1,&vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, pts.size()*sizeof(glm::vec2),
                 pts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    _buffers.push_back({vao,vbo});
    outCount = static_cast<GLsizei>(pts.size());
    return vao;
}

std::vector<glm::vec2> ShapeRenderer::generateEllipsePoints(int segments) const {
    std::vector<glm::vec2> pts;
    pts.reserve(segments + 2);
    pts.emplace_back(0.0f, 0.0f);
    for (int i = 0; i <= segments; ++i) {
        float a = float(i) / segments * 2.0f * glm::pi<float>();
        pts.emplace_back(std::cos(a), std::sin(a));
    }
    return pts;
}

GLuint ShapeRenderer::makeEllipseVAO(int segments, GLsizei& outCount) {
    auto pts = generateEllipsePoints(segments);
    return makePolygonVAO(pts, outCount);
}

GLuint ShapeRenderer::makeSquareVAO(GLsizei& outCount) {
    std::vector<glm::vec2> pts = {
        {0,0}, {-0.5f,-0.5f}, {0.5f,-0.5f},
        {0.5f, 0.5f}, {-0.5f, 0.5f}, {-0.5f,-0.5f}
    };
    return makePolygonVAO(pts, outCount);
}

GLuint ShapeRenderer::makeRectangleVAO(GLsizei& outCount, float w, float h) {
    std::vector<glm::vec2> pts = {
        {0,0}, {-w/2,-h/2}, {w/2,-h/2},
        {w/2, h/2}, {-w/2, h/2}, {-w/2,-h/2}
    };
    return makePolygonVAO(pts, outCount);
}

void ShapeRenderer::drawVAO(GLuint vao, GLsizei count,
                            glm::vec2 pos, float angle,
                            glm::vec2 scale, glm::vec3 color,
                            const Shader& shader)
{
    glm::mat4 M(1.0f);
    M = glm::translate(M, glm::vec3(pos, 0.0f));
    M = glm::rotate   (M, glm::radians(angle),
                    glm::vec3(0,0,1));
    M = glm::scale    (M, glm::vec3(scale,1.0f));
    shader.use();
    shader.setMat4("uModel", &M[0][0]);
    shader.setVec3("uColor", color.x, color.y, color.z);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, count);
    glBindVertexArray(0);
}
