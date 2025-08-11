// Shapes.cpp
#include "Shapes.h"
#include "Renderer.h"

void Circle::draw() const {
    Renderer::instance().showAndRun(*this);
}
void Square::draw() const {
    Renderer::instance().showAndRun(*this);
}
void Rectangle::draw() const {
    Renderer::instance().showAndRun(*this);
}
void Triangle::draw() const {
    Renderer::instance().showAndRun(*this);
}
void Polygon::draw() const {
    Renderer::instance().showAndRun(*this);
}
