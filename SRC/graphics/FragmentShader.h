//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_FRAGMENTSHADER_H
#define CHESTHUNTER_FRAGMENTSHADER_H

#include "Shader.h"

class FragmentShader : public Shader{
public:
    FragmentShader (){
        this->type = GL_FRAGMENT_SHADER;
        this->code =
                "#version 300 es \n"
                "precision mediump float ; \n"
                "in vec4 colorForFragment;\n"
                "out vec4 color; \n"
                "void main (){"
                "color = colorForFragment;\n"
                "}\0";
    }
};
#endif //CHESTHUNTER_FRAGMENTSHADER_H
