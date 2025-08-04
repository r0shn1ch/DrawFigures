# DrawFigures

Простая кроссплатформенная программа на C++ 20 и OpenGL, которая рисует в окне фигуры (
(квадрат, прямоугольник, круг, эллипс и шестиугольник), или произвольные, если указать точки в параметрах. Потом они разлетаются к краям окна и отскакивают от него (сделано через шейдер, можно отключить). 

Реализовано через GLFW + GLEW + GLM + VAO/VBO и GLSL-шейдеры.  
Также есть Google Tests, небольшой комплект тестов проверяет базовую корректность работы. Сама библиотека подключается через CMake.

Запускать тесты можно через: 
```bash
ctest --output-on-failure
```

### Зависимости

- **CMake ≥ 3.15**
- Компилятор с поддержкой **C++20** (GCC/Clang)
- Библиотеки:
  - **GLFW** (окно + контекст)
  - **GLEW** (загрузка OpenGL-функций)
  - **GLM** (математика)
  - **OpenGL** (вендорские заголовки + библиотека)

### Сборка и запуск на Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake libglfw3-dev libglew-dev libglm-dev
```
а затем либо собрать в консоли:
```bash
cd DrawFigures
mkdir build && cd build
cmake ..
cmake --build .
#запуск: <папка с репозиторием>/build/src/DrawFiguresApp
```
либо просто открыть файл CMakeLists.txt из IDE которая это поддерживает, например Qt Creator, и нажать на кнопку запуска

### Сборка и запуск на Windows
сначала установить vcpkg (если его нет) по инструкции: https://learn.microsoft.com/en-us/vcpkg/get_started/get-started

затем установить библиотеки для работы с OpenGL:
```
.\vcpkg install glfw3 glew glm
.\vcpkg integrate install
```
затем собрать проект 
```
mkdir build; cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[путь_к_vcpkg]\scripts\buildsystems\vcpkg.cmake
cmake --build . 
```
и запустить через DrawFiguresApp.exe

### Как рисовать свои фигуры
В текущем main.cpp уже есть пример пяти фигур:

```cpp
 renderer.drawVAO(sqVAO, sqCnt, posSq, 30.0f, {55.f, 55.f}, {1, 0, 0}, shader); // квадрат
 renderer.drawVAO(rectVAO, rectCnt, posRect, -15.0f, {1, 1}, {0, 1, 0}, shader); // прямоугольник
 renderer.drawVAO(circVAO, circCnt, posCirc, 0.0f, {55.f, 55.f}, {0, 0, 1}, shader); // круг
 renderer.drawVAO(ellVAO, ellCnt, posEll, 45.0f, {55.f, 80.f}, {1, 1, 0}, shader); // эллипс
 renderer.drawVAO(hexVAO, hexCnt, posHex, 0.0f, {1, 1}, {1, 0, 1}, shader); // шестиугольник
```

Параметры для каждого вызова:
- vao и count — объекты, подготовленные заранее в начале main().
- glm::vec2 pos — центр фигуры в нормализованных координатах (x, y от −1 до +1).
- float angle — поворот в градусах.
- glm::vec2 scale — масштаб (для круга/эллипса: радиусы по X/Y; для квадрата/прямоугольника: ширина/высота относительно базовой единицы).
- glm::vec3 color — цвет RGB (каждое 0…1).

Если хотите нарисовать сразу несколько разных фигур — добавьте новые строки R.drawVAO(...) в цикл рендера.

### Как добавить новые фигуры
В ShapeRenderer.cpp есть метод

```cpp
GLuint makePolygonVAO(const std::vector<glm::vec2>& pts, GLsizei& outCount);
```

В начале main() создайте std::vector<glm::vec2> pts, заполните нужными координатами, например:

```cpp
std::vector<glm::vec2> star = {
  {0,0}, { 0.0f, 0.5f},
         { 0.1f, 0.1f},
  {-0.5f, 0.0f}, {0.1f,-0.1f},
         {0.0f,-0.5f},
  { 0.1f,-0.1f}  // и замыкаем
};
GLsizei starCnt;
GLuint starVAO = R.makePolygonVAO(star, starCnt);
```
В рендер-цикле:

```cpp
R.drawVAO(starVAO, starCnt, {0,0}, 0.0f, {1,1}, {1,0.5f,0}, shader);
```
