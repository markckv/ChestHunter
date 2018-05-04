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
   MemoryHandler memoryHandler =  managerMemory.addModel( loaderModel.load("../models/GRASS.obj"));
    models.insert({"GRASS", memoryHandler});
    memoryHandler = managerMemory.addModel( loaderModel.load("../models/CHEST.obj"));
    models.insert({"CHEST", memoryHandler});
    memoryHandler = managerMemory.addModel( loaderModel.load("../models/HERO.obj"));
    models.insert({"HERO", memoryHandler});
    memoryHandler = managerMemory.addModel(loaderModel.load("../models/FOREST.obj"));
    models.insert({"FOREST", memoryHandler});
    memoryHandler = managerMemory.addModel(loaderModel.load("../models/FOREST2.obj"));
    models.insert({"FOREST2", memoryHandler});
    memoryHandler = managerMemory.addModel(loaderModel.load("../models/FOREST3.obj"));
    models.insert({"FOREST3", memoryHandler});
    memoryHandler = managerMemory.addModel(loaderModel.load("../models/FOREST4.obj"));
    models.insert({"FOREST4", memoryHandler});



}
