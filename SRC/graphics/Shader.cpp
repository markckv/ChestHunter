//
// Created by mark on 01.04.18.
//

#include <stdexcept>
#include "Shader.h"

void Shader::create() {
    id = glCreateShader(type);
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);
    GLint ok;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLchar log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        throw std::logic_error(log);

    }
}

Shader::operator GLuint() {
    return id;
}
