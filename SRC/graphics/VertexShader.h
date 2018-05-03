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
                        "uniform mat4 transform;\n"
                        "uniform int startid;\n"
                        "uniform vec3 lightP; \n"
                        "uniform vec3 lightC; \n"
                "layout (location = 0) in vec3 pos; \n"
                "layout (location = 1) in vec3 normal; \n"
                "layout (location = 2) in vec2 uv; \n"
                "layout (location = 3) in vec3 color; \n"
                "out vec4 colorForFragment; \n"
                "void main(){ \n"
                "gl_Position = projection_view * (vec4(pos, 1.0));\n"
                        "vec3 toLight = ((vec4(lightP, 1.0)) - transform * (vec4(pos, 1.0))).xyz;\n"
                        "vec3 normal1 = (transform * (vec4(normal, 0.0))).xyz;\n"
                        "float a = (toLight.x * normal1.x + toLight.y * normal1.y + toLight.z * normal1.z) ;\n"
                        "float b = length(toLight);\n"
                        "float c = length(normal1);\n"
                        "float x = a/(b*c) ;\n"
                        "colorForFragment = vec4(color+lightC* clamp(x, 0.0,1.0), 1.0f);\n"
                "}\0";
    }
};
//"colorForFragment = vec4(color+lightC*clamp(x, 0.0,1.0), 1.0f);\n"

#endif //CHESTHUNTER_VERTEXSHADER_H
