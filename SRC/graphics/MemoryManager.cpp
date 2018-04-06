//
// Created by mark on 01.04.18.
//

#include <stdexcept>
#include "MemoryManager.h"
#include "Vertex.h"
#include "MemoryHandler.h"

MemoryManager::MemoryManager(int capacity) {
this->capacity = capacity;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    char nullData[capacity* sizeof(Vertex)];
    glBufferData(GL_ARRAY_BUFFER,capacity* sizeof(Vertex), nullData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (GLvoid *)(sizeof(glm::vec3)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (GLvoid *)(sizeof(glm::vec3) * 2));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) , (GLvoid *)(sizeof(glm::vec3) * 2 + sizeof(glm::vec2)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}

MemoryManager::operator GLuint() {
    return id;
}

MemoryHandler MemoryManager::addModel(Model model) {
    if(model.size()+ this->loadedVertexes > this->capacity){
        throw std::logic_error("Memory is over");
    }
glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex)*(this->loadedVertexes), model.size()*sizeof(Vertex), model.data());
    loadedVertexes+=  model.size();
    return {this->loadedVertexes- model.size() ,model.size()};
}
