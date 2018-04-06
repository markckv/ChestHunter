//
// Created by mark on 05.04.18.
//

#include "Drawer.h"
#include "MemoryHandler.h"
#include "MemoryManager.h"
#include <string>
#include <bits/unordered_map.h>
std::unordered_map <std::string , MemoryHandler> models;
Drawer::Drawer() {
    MemoryManager memoryManager(1000);
    models ["chest"] =



}
void draw(std::string nameModel){
   MemoryHandler memoryHandler = models.unordered_map::at(nameModel);
    if (nameModel == "SIGN_GRASS") {
        glDrawArrays(GL_TRIANGLES, 6 * 2 * 3, 6 * 2 * 3);
    }
    if (nameModel  == "SIGN_FOREST") {
        glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
    }
    if (nameModel == "SIGN_CHEST") {
        glDrawArrays(GL_TRIANGLES, 6 * 2 * 3 * 2, 6 * 2 * 3);
    }


}
