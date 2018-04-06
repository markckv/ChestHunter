//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_VERTEX_H
#define CHESTHUNTER_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct Vertex{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 color;
};

using Model = std::vector<Vertex>;

#endif //CHESTHUNTER_VERTEX_H
