//
// Created by mark on 05.04.18.
//

#include "Drawer.h"
#include "GenerateCube.h"
#include "MemoryHandler.h"
#include "MemoryManager.h"
#include "LoaderModel.h"
#include <string>
#include <bits/unordered_map.h>
using namespace glm;
//Drawer::Drawer() : managerMemory(1000000){
//    GenerateCube generateCube;
//    Model forest;
//    Model chest;
//    Model grass;
//    Model hero;
//    generateCube.generateCube(forest, vec3(-10, -40, -10), 20, 80, 20);
//    models.insert({"FOREST", managerMemory.addModel(forest)});
//    generateCube.generateCube(grass, vec3(-10, -0.5, -10), 20, 1, 20);
//    models.insert({"GRASS", managerMemory.addModel(grass)});
//    generateCube.generateCube(chest, vec3(-10, -2.5, -10), 20, 5, 20);
//    models.insert({"CHEST", managerMemory.addModel(chest)});
//    generateCube.generateCube(hero, vec3(-10, -2.5, -10), 20, 10, 20);
//    models.insert({"HERO", managerMemory.addModel(hero)});
//}
void Drawer::draw(std::string nameModel){
    MemoryHandler memoryHandler = models.at(nameModel);
    glDrawArrays(GL_TRIANGLES, memoryHandler.start, memoryHandler.size);

}
Drawer::Drawer() : managerMemory(1000000){
    LoaderModel loaderModel;
   MemoryHandler memoryHandler =  managerMemory.addModel(loaderModel.load("../models/forest.obj"));
    models.insert({"FOREST", memoryHandler});
    memoryHandler = managerMemory.addModel( loaderModel.load("../models/chest.obj"));
    models.insert({"CHEST", memoryHandler});
    memoryHandler = managerMemory.addModel( loaderModel.load("../models/Hero.obj"));
    models.insert({"HERO", memoryHandler});
    memoryHandler = managerMemory.addModel( loaderModel.load("../models/Grass.obj"));
    models.insert({"GRASS", memoryHandler});


}
