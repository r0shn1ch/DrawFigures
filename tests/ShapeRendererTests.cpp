#include <gtest/gtest.h>
#include "ShapeRenderer.h"
#include <glm/glm.hpp>

// Проверим, что для N сегментов эллипса вернётся N+2 точек (центр + N+1)
TEST(EllipseGeneration, CorrectCount) {
    ShapeRenderer R;
    for(int segs : {3, 8, 64, 128}) {
        auto pts = R.generateEllipsePoints(segs);
        EXPECT_EQ(pts.size(), size_t(segs+2));
    }
}

// Первая точка эллипса должна быть (0,0), вторая — на (1,0)
TEST(EllipseGeneration, FirstPoints) {
    ShapeRenderer R;
    auto pts = R.generateEllipsePoints(8);
    ASSERT_GE(pts.size(), 2u);
    EXPECT_FLOAT_EQ(pts[0].x, 0.0f);
    EXPECT_FLOAT_EQ(pts[0].y, 0.0f);
    EXPECT_NEAR(pts[1].x, 1.0f, 1e-6f);
    EXPECT_NEAR(pts[1].y, 0.0f, 1e-6f);
}

// Проверим, что makePolygonVAO возвращает ненулевой VAO и правильный count
TEST(PolygonVAO, NonZeroAndCount) {
    ShapeRenderer R;
    std::vector<glm::vec2> pts = {
        {0,0}, {1,0}, {1,1}, {0,1}, {0,0}
    };
    GLsizei cnt = 0;
    GLuint vao = R.makePolygonVAO(pts, cnt);
    EXPECT_NE(vao, 0u);
    EXPECT_EQ(cnt, 5);
}

// Квадрат: должен давать 6 точек (центр + 5 по углам+замыкание)
TEST(SquareVAO, CountIsSix) {
    ShapeRenderer R;
    GLsizei cnt = 0;
    GLuint vao = R.makeSquareVAO(cnt);
    EXPECT_NE(vao, 0u);
    EXPECT_EQ(cnt, 6);
}

// Прямоугольник: проверим, что счётчик совпадает с квадратом
TEST(RectangleVAO, CountMatchesSquare) {
    ShapeRenderer R;
    GLsizei c1 = 0, c2 = 0;
    R.makeSquareVAO(c1);
    R.makeRectangleVAO(c2, 2.0f, 1.0f);
    EXPECT_EQ(c1, c2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
