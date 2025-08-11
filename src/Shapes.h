#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <IShape.h>

class Circle : public IShape {
public:
    Circle(float radius = 0.5f, int segments = 48) {
        verts.reserve(size_t(segments) + 2);
        verts.emplace_back(0.0f, 0.0f);
        for (int i = 0; i <= segments; ++i) {
            float a = 2.0f * 3.14159265358979323846f * (float(i) / float(segments));
            verts.emplace_back(radius * std::cos(a), radius * std::sin(a));
        }
    }
    const std::vector<glm::vec2>& getVertices() const override { return verts; }
    GLenum getDrawMode() const override { return GL_TRIANGLE_FAN; }
    void draw() const override;
private:
    std::vector<glm::vec2> verts;
};

class Square : public IShape {
public:
    explicit Square(float side = 1.0f) {
        float h = side * 0.5f;
        verts = { {0.0f,0.0f}, {-h,-h}, {h,-h}, {h,h}, {-h,h}, {-h,-h} };
    }
    const std::vector<glm::vec2>& getVertices() const override { return verts; }
    GLenum getDrawMode() const override { return GL_TRIANGLE_FAN; }
    void draw() const override;
private:
    std::vector<glm::vec2> verts;
};

class Rectangle : public IShape {
public:
    Rectangle(float w = 1.0f, float h = 0.5f) {
        float hw = w * 0.5f, hh = h * 0.5f;
        verts = { {0,0}, {-hw,-hh}, {hw,-hh}, {hw,hh}, {-hw,hh}, {-hw,-hh} };
    }
    const std::vector<glm::vec2>& getVertices() const override { return verts; }
    GLenum getDrawMode() const override { return GL_TRIANGLE_FAN; }
    void draw() const override;
private:
    std::vector<glm::vec2> verts;
};

class Triangle : public IShape {
public:
    Triangle(const glm::vec2& a = {-0.5f,-0.5f}, const glm::vec2& b = {0.0f,0.5f}, const glm::vec2& c = {0.5f,-0.5f}) {
        verts = { a, b, c };
    }
    const std::vector<glm::vec2>& getVertices() const override { return verts; }
    GLenum getDrawMode() const override { return GL_TRIANGLES; }
    void draw() const override;
private:
    std::vector<glm::vec2> verts;
};

class Polygon : public IShape {
public:
    Polygon(const std::vector<glm::vec2>& pts) : verts(pts) {}
    const std::vector<glm::vec2>& getVertices() const override { return verts; }
    GLenum getDrawMode() const override { return GL_LINE_LOOP; }
    void draw() const override;
private:
    std::vector<glm::vec2> verts;
};
