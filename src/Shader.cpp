#include "Shader.h"
#include <iostream>
#include <vector>

static void printLog(GLuint obj, bool prog) {
    GLint len = 0;
    if (prog) glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);
    else      glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);
    if (len <= 1) return;
    std::vector<char> buf((size_t(len)));
    if (prog) glGetProgramInfoLog(obj, len, nullptr, buf.data());
    else      glGetShaderInfoLog(obj, len, nullptr, buf.data());
    std::cerr << buf.data() << "\n";
}

Shader::Shader(const char* vsSrc, const char* fsSrc) {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);
    checkCompile(vs, false);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);
    checkCompile(fs, false);
    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);
    checkCompile(m_id, true);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() { if (m_id) glDeleteProgram(m_id); }
void Shader::use() const noexcept { if (m_id) glUseProgram(m_id); }
GLint Shader::getLoc(const std::string& name) const {
    auto it = m_cache.find(name);
    if (it != m_cache.end()) return it->second;
    GLint loc = glGetUniformLocation(m_id, name.c_str());
    m_cache[name] = loc;
    return loc;
}
void Shader::setMat4(const std::string& name, const float* mat) const noexcept {
    glUniformMatrix4fv(getLoc(name), 1, GL_FALSE, mat);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const noexcept {
    glUniform3f(getLoc(name), x, y, z);
}
void Shader::checkCompile(GLuint obj, bool isProgram) {
    if (!isProgram) {
        GLint ok = GL_FALSE;
        glGetShaderiv(obj, GL_COMPILE_STATUS, &ok);
        if (!ok) printLog(obj, false);
    } else {
        GLint ok = GL_FALSE;
        glGetProgramiv(obj, GL_LINK_STATUS, &ok);
        if (!ok) printLog(obj, true);
    }
}
