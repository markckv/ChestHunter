//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_VERTEXSHADER_H
#define CHESTHUNTER_VERTEXSHADER_H

#include "Shader.h"

class VertexShader : public Shader {
public:
    VertexShader() {
        this->type = GL_VERTEX_SHADER;
        this->code =
                "#version 300 es \n"
                "uniform mat4 projection_view;\n"
                "uniform int startid;\n"
                "layout (location = 0) in vec3 pos; \n"
                "layout (location = 1) in vec3 normal; \n"
                "layout (location = 2) in vec2 uv; \n"
                "layout (location = 3) in vec3 color; \n"
                "out vec4 colorForFragment; \n"
                "void main(){ \n"
                "gl_Position = projection_view * (vec4(pos, 1.0));\n"
                "colorForFragment = vec4(color, 1.0f);\n"
                "}\0";
    }
};

#endif //CHESTHUNTER_VERTEXSHADER_H
