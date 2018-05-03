//
// Created by mark on 08.04.18.
//

#include <vector>
#include <glm/vec3.hpp>
#include <fstream>
#include "LoaderModel.h"
#include "Vertex.h"
#include <string>
#include <glm/vec2.hpp>
#include <algorithm>
#include <iostream>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline bool space(char c) {
    if (c == '/')
        return true;
    return false;
}

inline bool notspace(char c) {
    return !space(c);
}

//break a sentence into words
std::vector<std::string> split(const std::string &s) {
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;
    iter i = s.begin();
    while (i != s.end()) {
        i = std::find_if(i, s.end(), notspace); // find the beginning of a word
        iter j = std::find_if(i, s.end(), space); // find the end of the same word
        if (i != s.end()) {
            ret.push_back(std::string(i, j)); //insert the word into vector
            i = j; // repeat 1,2,3 on the rest of the line.
        }
    }
    return ret;
}

Model LoaderModel::load(std::string name) {
    std::vector<glm::vec3> pos, normals;
    std::vector<glm::vec2> uvs;
    std::vector<int> indexPos, indexNormals, indexUv;
    std::ifstream file;
    file.open(name);
    if (!file.is_open()) throw std::logic_error("CAN'T OPEN THIS FILE!" + name);
    std::string type;
    glm::mat4 scale;
    scale = glm::scale(scale, glm::vec3(2.55,2.55,2.55));
    glm::vec3 color;
    while (!file.eof()) {

        file >> type;
        if (type == "v") {
            glm::vec3 p;
            file >> p.x >> p.y >> p.z;
            pos.push_back(p);
        }
        if (type == "vn") {
            glm::vec3 vn;
            file >> vn.x >> vn.y >> vn.z;
            normals.push_back(vn);
        }
        if (type == "vt") {
            glm::vec2 vt;
            file >> vt.x >> vt.y;
            uvs.push_back(vt);
        }
        if (type == "f") {
            for (int i = 0; i < 3; i++) {
                std::string vertex;
                file >> vertex;
                std::cout << vertex <<  std::endl;
                std::vector<std::string> vector = split(vertex);
                indexPos.push_back(std::stoi(vector[0]));
                indexUv.push_back(std::stoi(vector[1]));
                indexNormals.push_back(std::stoi(vector[2]));

            }
        }

        if (type == "color") {
            file >> color.x >> color.y >> color.z;

        }

//        std::cout << "faces: " << indexNormals.size()/3 << std::endl;
//        std::cout << "uvs: " << uvs.size() << std::endl;
//        std::cout << "pos: " << pos.size() << std::endl;
//        std::cout << "normal: " << normals.size() << std::endl;

        std::cout << type  << std::endl;
    }
    Model model;
    srand(time(nullptr));
    for (int i = 0; i < indexPos.size(); i++) {
        Vertex vertex;
        glm::vec4 vec4(pos[indexPos[i]-1], 1);
        vec4= scale * vec4;
        glm::vec3 vec3 (vec4.x, vec4.y, vec4.z);
        vertex.pos = vec3;
        vertex.color = glm::vec3(color.x, color.y, color.z);
        vertex.normal = normals[indexNormals[i]-1];
//        vertex.uv = uvs[indexUv[i]];
        model.push_back(vertex);
    }
    return model;
}


