#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>

class Shader {
public:
    Shader() = default;
    Shader(const char* vsSrc, const char* fsSrc);
    ~Shader();
    void use() const noexcept;
    void setMat4(const std::string& name, const float* mat) const noexcept;
    void setVec3(const std::string& name, float x, float y, float z) const noexcept;
private:
    GLuint m_id{0};
    mutable std::unordered_map<std::string, GLint> m_cache;
    GLint getLoc(const std::string& name) const;
    static void checkCompile(GLuint obj, bool isProgram);
};
