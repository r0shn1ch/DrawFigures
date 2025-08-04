#include "Shader.h"
#include <iostream>
#include <unordered_map>

void Shader::checkCompile(GLuint obj, bool isShader) {
    GLint success = 0;
    if (isShader) glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
    else          glGetProgramiv(obj, GL_LINK_STATUS,  &success);
    if (!success) {
        char log[512];
        if (isShader) glGetShaderInfoLog(obj, 512, nullptr, log);
        else          glGetProgramInfoLog(obj, 512, nullptr, log);
        std::cerr << (isShader ? "Shader" : "Program")
                  << " compile/link error:\n" << log << "\n";
    }
}

Shader::Shader(const char* vsSrc, const char* fsSrc) {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);
    checkCompile(vs, true);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);
    checkCompile(fs, true);

    _id = glCreateProgram();
    glAttachShader(_id, vs);
    glAttachShader(_id, fs);
    glLinkProgram(_id);
    checkCompile(_id, false);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (_id) glDeleteProgram(_id);
}

void Shader::use() const noexcept {
    glUseProgram(_id);
}

GLint Shader::getUniformLocation(const std::string& name) const noexcept {
    if (_cache.count(name)) return _cache.at(name);
    GLint loc = glGetUniformLocation(_id, name.c_str());
    _cache[name] = loc;
    return loc;
}

void Shader::setMat4(const std::string& name, const float* mat) const noexcept {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, mat);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const noexcept {
    glUniform3f(getUniformLocation(name), x, y, z);
}
