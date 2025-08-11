// main.cpp
#include "Shapes.h"

int main() {
    Circle c(0.4f, 64);
    Square s(0.8f);
    Triangle t({-0.5f,-0.5f}, {0.0f,0.5f}, {0.5f,-0.5f});
    Polygon p({{ -0.3f,0.0f }, {0.0f,0.4f}, {0.3f,0.0f }});
    Rectangle r(0.8f, 0.4f);

    s.setColor({0.9f, 0.7f, 0.3f});
    s.setScale({0.8f, 0.8f});

    //c.draw();
    s.draw();
    //t.draw();
    //p.draw();
    //r.draw();
    return 0;
}

