//
// Created by mark on 01.04.18.
//

#ifndef CHESTHUNTER_MEMORYMANAGER_H
#define CHESTHUNTER_MEMORYMANAGER_H


#include <GLES3/gl3.h>
#include "Vertex.h"
#include "MemoryHandler.h"

class MemoryManager {
    int capacity;
    int loadedVertexes=0;
    GLuint id;
public:
    MemoryManager(int capacity);
    operator GLuint();
MemoryHandler addModel(Model model);

};


#endif //CHESTHUNTER_MEMORYMANAGER_H
