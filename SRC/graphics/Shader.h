//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_SHADER_H
#define CHESTHUNTER_SHADER_H


#include <GLES3/gl3.h>

class Shader {
protected:
    GLenum type;
    const GLchar * code;
    GLuint id;
public:
    void create();
    operator GLuint();
};


#endif //CHESTHUNTER_SHADER_H
