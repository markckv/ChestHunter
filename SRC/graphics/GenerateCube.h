//
// Created by mark on 06.04.18.
//

#ifndef CHESTHUNTER_GENERATECUBE_H
#define CHESTHUNTER_GENERATECUBE_H


#include <glm/glm.hpp>
#include "Vertex.h"

using namespace glm;
class GenerateCube {
public:
    void generateQuad(Model &out, vec3 bl, vec3 br, vec3 ul, vec3 ur, vec3 color);

    void generateCube(Model &out, vec3 leftBottom, float lenght, float width, float height);
};


#endif //CHESTHUNTER_GENERATECUBE_H
