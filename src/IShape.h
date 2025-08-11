#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

class IShape {
public:
    virtual ~IShape() = default;
    virtual const std::vector<glm::vec2>& getVertices() const = 0;
    virtual GLenum getDrawMode() const = 0;
    virtual void draw() const = 0;

    void setPosition(const glm::vec2& p) { pos = p; }
    glm::vec2 getPosition() const { return pos; }

    void setScale(const glm::vec2& s) { scale = s; }
    glm::vec2 getScale() const { return scale; }

    void setRotation(float deg) { angle = deg; }
    float getRotation() const { return angle; }

    void setColor(const glm::vec3& c) { color = c; }
    glm::vec3 getColor() const { return color; }

private:
    glm::vec2 pos   {0.0f, 0.0f};
    glm::vec2 scale {1.0f, 1.0f};
    float     angle {0.0f};
    glm::vec3 color {1.0f, 1.0f, 1.0f};
};
