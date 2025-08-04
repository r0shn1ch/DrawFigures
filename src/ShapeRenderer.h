#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

class ShapeRenderer {
public:
    ShapeRenderer() = default;
    ~ShapeRenderer();

    // полигон из точек
    GLuint makePolygonVAO(const std::vector<glm::vec2>& pts, GLsizei& outCount);

    // эллипс
    std::vector<glm::vec2> generateEllipsePoints(int segments) const;
    GLuint makeEllipseVAO(int segments, GLsizei& outCount);

    // квадрат, прямоугольник
    GLuint makeSquareVAO(GLsizei& outCount);
    GLuint makeRectangleVAO(GLsizei& outCount, float width, float height);

    // произвольный VAO
    void drawVAO(GLuint vao, GLsizei count,
                 glm::vec2 pos, float angle,
                 glm::vec2 scale, glm::vec3 color,
                 const class Shader& shader);

private:
    struct Buffer { GLuint vao, vbo; };
    std::vector<Buffer> _buffers;
};
