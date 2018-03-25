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

using namespace glm;

class Graphics {
    GLuint gLuint2;

    void addVec3(std::vector<GLfloat> &out, vec3 vec) {
        out.push_back(vec.x);
        out.push_back(vec.y);
        out.push_back(vec.z);
    }

    void generateQuad(std::vector<GLfloat> &out, vec3 bl, vec3 br, vec3 ul, vec3 ur, vec3 color) {
        //First triangle
        addVec3(out, bl);
        addVec3(out, color);
        addVec3(out, ul);
        addVec3(out, color);
        addVec3(out, ur);
        addVec3(out, color);
        //Second triangle
        addVec3(out, bl);
        addVec3(out, color);
        addVec3(out, br);
        addVec3(out, color);
        addVec3(out, ur);
        addVec3(out, color);
    }

    void generateCube(std::vector<GLfloat> &out, glm::vec3 leftBottom, float lenght, float width, float height) {
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
    GLuint createShader(const GLchar *gLchar, GLenum gLenum) {
        GLuint gLuint = glCreateShader(gLenum);
        glShaderSource(gLuint, 1, &gLchar, nullptr);
        glCompileShader(gLuint);
        GLint ok;
        glGetShaderiv(gLuint, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            GLchar log[512];
            glGetShaderInfoLog(gLuint, 512, nullptr, log);
        }
        return gLuint;
    }
public:
    GLuint createShaders() {
        auto *pfGPU = const_cast<GLchar *>("#version 300 es \n"
                "uniform mat4 projection_view;\n"
                "uniform int startid;\n"
                "layout (location = 0) in vec3 v3; \n"
                "layout (location = 1) in vec3 c; \n"
                "out vec4 colorForFragment; \n"
                "void main(){ \n"
                "int arrSize = 100;\n"
                "gl_Position = projection_view * (vec4(v3, 1.0));\n"
                "colorForFragment = vec4(c, 1.0f);\n"
                "}\0");
        auto *fragmentGPU = const_cast<GLchar *>("#version 300 es \n"
                "precision mediump float ; \n"
                "in vec4 colorForFragment;\n"
                "out vec4 color; \n"
                "void main (){"
                "color = colorForFragment;\n"
                "}\0");
        GLuint gLuint = createShader(pfGPU, GL_VERTEX_SHADER);
        GLuint gLuint1 = createShader(fragmentGPU, GL_FRAGMENT_SHADER);
        gLuint2 = glCreateProgram();
        glAttachShader(gLuint2, gLuint);
        glAttachShader(gLuint2, gLuint1);
        GLint gLint;
        glLinkProgram(gLuint2);
        glGetProgramiv(gLuint2, GL_LINK_STATUS, &gLint);
        if (!gLint) {
            GLchar gLchar[512];
            glGetProgramInfoLog(gLuint2, 512, nullptr, gLchar);
        }
        std::vector<GLfloat> vertexes;
        generateCube(vertexes, vec3(-10, -10, -10), 20, 20, 20);
        generateCube(vertexes, vec3(-10, -0.5, -10), 20, 1, 20);
        generateCube(vertexes, vec3(-10, -2.5, -10), 20, 5, 20);
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid *) (3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glm::mat4 transform;
        glm::mat4 endTransform;
        GLuint transformGPULoc = glGetUniformLocation(gLuint2, "projection_view");
        GLuint transformGPULoc2 = glGetUniformLocation(gLuint2, "startid");
        glUseProgram(gLuint2);
        return  gLuint2;
    }


};


#endif //CHESTHUNTER_GRAPHICS_H
