//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_SHADERPROGRAM_H
#define CHESTHUNTER_SHADERPROGRAM_H


#include <GLES3/gl3.h>
#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram {


    FragmentShader fragmentShader;
    VertexShader vertexShader;

    GLuint id;
public:
    ShaderProgram(FragmentShader fragmentShader, VertexShader vertexShader);
    ShaderProgram();
    void create();
    operator GLuint() ;
};


#endif //CHESTHUNTER_SHADERPROGRAM_H
