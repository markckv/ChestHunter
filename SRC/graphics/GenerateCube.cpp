//
// Created by mark on 06.04.18.
//
#include <glm/glm.hpp>
#include "GenerateCube.h"
#include "Vertex.h"
using namespace glm;
void GenerateCube::generateQuad(Model &out, vec3 bl, vec3 br, vec3 ul, vec3 ur, vec3 color) {
    //First triangle
    out.push_back({bl, glm::vec3(0,0,0),glm::vec2(0,0), color});
    out.push_back({ul, glm::vec3(0,0,0),glm::vec2(0,0), color});
    out.push_back({ur, glm::vec3(0,0,0),glm::vec2(0,0), color});
    out.push_back({bl, glm::vec3(0,0,0),glm::vec2(0,0), color});
    out.push_back({br, glm::vec3(0,0,0),glm::vec2(0,0), color});
    out.push_back({ur, glm::vec3(0,0,0),glm::vec2(0,0), color});



}

void GenerateCube::generateCube(Model &out, glm::vec3 leftBottom, float lenght, float width, float height) {
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
