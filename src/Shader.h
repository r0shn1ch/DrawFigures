#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();
    void use() const noexcept;
    GLint getUniformLocation(const std::string& name) const noexcept;
    void setMat4(const std::string& name, const float* mat) const noexcept;
    void setVec3(const std::string& name, float x, float y, float z) const noexcept;

    GLuint id() const noexcept { return _id; }

private:
    GLuint _id = 0;
    mutable std::unordered_map<std::string,GLint> _cache;
    static void checkCompile(GLuint obj, bool isShader);
};
