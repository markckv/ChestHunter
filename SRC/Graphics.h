//
// Created by mark on 20.03.18.
//

#ifndef CHESTHUNTER_GRAPHICS_H
#define CHESTHUNTER_GRAPHICS_H

#include <iostream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>
#include "graphics/Shader.h"
#include "graphics/FragmentShader.h"
#include "graphics/VertexShader.h"
#include "graphics/ShaderProgram.h"
#include "graphics/MemoryManager.h"

using namespace glm;

class Graphics {

    void generateQuad(Model &out, vec3 bl, vec3 br, vec3 ul, vec3 ur, vec3 color) {
        //First triangle
        out.push_back({bl, glm::vec3(0,0,0),glm::vec2(0,0), color});
        out.push_back({ul, glm::vec3(0,0,0),glm::vec2(0,0), color});
        out.push_back({ur, glm::vec3(0,0,0),glm::vec2(0,0), color});
        out.push_back({bl, glm::vec3(0,0,0),glm::vec2(0,0), color});
        out.push_back({br, glm::vec3(0,0,0),glm::vec2(0,0), color});
        out.push_back({ur, glm::vec3(0,0,0),glm::vec2(0,0), color});


    }

    void generateCube(Model &out, glm::vec3 leftBottom, float lenght, float width, float height) {
        vec3 dbl = leftBottom;
        vec3 dul = leftBottom + vec3(0, 0, height);
        vec3 dbr = dbl + vec3(lenght, 0, 0);
        vec3 dur = dbl + vec3(lenght, 0, height);
        vec3 ubl = dbl + vec3(0, width, 0);
        vec3 uul = dul + vec3(0, width, 0);
        vec3 ubr = dbr + vec3(0, width, 0);
        vec3 uur = dur + vec3(0, width, 0);

        generateQuad(out, dbl, dbr, dul, dur, vec3(1, 0, 0));
        generateQuad(out, ubl, ubr, uul, uur, vec3(0, 1, 0));
        generateQuad(out, dbl, dbr, ubl, ubr, vec3(0, 0, 1));
        generateQuad(out, dul, dur, uul, uur, vec3(1, 0, 1));
        generateQuad(out, dbl, dul, ubl, uul, vec3(1, 1, 0));
        generateQuad(out, dbr, dur, ubr, uur, vec3(0, 1, 1));

    }

public:
    GLuint createShaders() {
        VertexShader vertexShader;
        FragmentShader fragmentShader;
        vertexShader.create();
        fragmentShader.create();
        ShaderProgram shaderProgram(fragmentShader, vertexShader);
        shaderProgram.create();
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glm::mat4 transform;
        glm::mat4 endTransform;
        GLint transformGPULoc = glGetUniformLocation((GLuint) shaderProgram, "projection_view");
        GLint transformGPULoc2 = glGetUniformLocation((GLuint) shaderProgram, "startid");
        glUseProgram((GLuint) shaderProgram);
        return (GLuint) shaderProgram;
    }


};


#endif //CHESTHUNTER_GRAPHICS_H
