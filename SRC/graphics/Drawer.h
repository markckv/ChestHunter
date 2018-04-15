//
// Created by mark on 05.04.18.
//

#ifndef CHESTHUNTER_DRAWER_H
#define CHESTHUNTER_DRAWER_H
#include <string>
#include <unordered_map>


#include "MemoryHandler.h"
#include "MemoryManager.h"

class Drawer {
    std::unordered_map <std::string , MemoryHandler> models;
    MemoryManager managerMemory;

public:
    Drawer();

    void draw(std::string nameModel);
};


#endif //CHESTHUNTER_DRAWER_H
