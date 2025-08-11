#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class IShape;
class Shader;

class Renderer {
public:
    static Renderer& instance();

    void init(int width, int height);
    void drawShape(const IShape* shape);
    int showAndRun(const IShape& shape, int w = 800, int h = 600, const char* title = "Shape");

private:
    Renderer() = default;
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    GLuint makeVAO(const std::vector<glm::vec2>& verts);

    std::unordered_map<const IShape*, GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
    Shader* m_shader = nullptr;
};
