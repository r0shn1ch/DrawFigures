# DrawFigures
small app for drawing figures on screen with pure OpenGL and GLFW

Доступные фигуры и параметры:
1) Circle(radius = 0.5f, segments = 48)
     - radius  : радиус круга (локальные координаты)
     - segments: количество сегментов (чем больше — тем более гладкий круг)
   Пример: Circle c(0.4f, 64);

2) Square(side = 1.0f)
     - side: длина стороны квадрата
   Пример: Square s(0.8f);

3) Rectangle(width = 1.0f, height = 0.5f)
     - width, height: размеры прямоугольника
   Пример: Rectangle r(0.8f, 0.4f);

4) Triangle(a, b, c)
     - a,b,c: три вершины в локальных координатах
   Пример: Triangle t({-0.5f,-0.5f}, {0.0f,0.5f}, {0.5f,-0.5f});

5) Polygon(points)
     - points: std::vector<glm::vec2> произвольных вершин
   Пример: Polygon p({{ -0.3f,0.0f }, {0.0f,0.4f}, {0.3f,0.0f }});

Howto:
1) Создать объект фигуры (например Circle c(0.4f,64);)
2) Задаёшь доп параметры (опционально):
        c.setPosition({0.0f, 0.0f});
        c.setScale({0.8f, 0.8f});
        c.setRotation(15.0f); градусы
        c.setColor({r,g,b});
3) Вызвать draw() — откроется окно и фигура отрисуется
