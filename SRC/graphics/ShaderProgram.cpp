//
// Created by mark on 01.04.18.
//

#include <stdexcept>
#include "ShaderProgram.h"

void ShaderProgram::create() {
    this->id = glCreateProgram();
    glAttachShader(this->id, (GLuint) vertexShader);
    glAttachShader(this->id, (GLuint) fragmentShader);
    GLint gLint;
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &gLint);
    if (!gLint) {
        GLchar error[512];
        glGetProgramInfoLog(this->id, 512, nullptr, error);
        throw std::logic_error(error);
    }

}

ShaderProgram::ShaderProgram(FragmentShader fragmentShader, VertexShader vertexShader) {
    this->fragmentShader = fragmentShader;
    this->vertexShader = vertexShader;
}
ShaderProgram::operator GLuint() {
    return id;
}
