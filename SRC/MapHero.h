//
// Created by mark on 27.05.18.
//

#ifndef CHESTHUNTER_MAPHERO_H
#define CHESTHUNTER_MAPHERO_H

struct Map {
    int *map;
    int size;
};
struct mapHero {
    Map map;
    int chestX;
    int chestY;
};
#endif //CHESTHUNTER_MAPHERO_H
