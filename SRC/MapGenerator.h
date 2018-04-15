//
// Created by mark on 18.03.18.
//

#ifndef CHESTHUNTER_MAPGENERATOR_H
#define CHESTHUNTER_MAPGENERATOR_H


#include <cstring>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iostream>
#include "GameObject.h"

class MapGenerator {
public:
    struct Map {
        int *map;
        int size;
    };
    struct mapHero {
        Map map;
        int heroX;
        int heroY;
        int chestX;
        int chestY;
    };


    std::pair<int , int> createHero(Map map) {
        int heroX, heroY;
        heroX = rand() % map.size;
        heroY = rand() % map.size;
        while (map.map[heroX * map.size + heroY] == SIGN_FOREST) {
            heroX = rand() % map.size;
            heroY = rand() % map.size;
        }
        map.map[heroX * map.size + heroY] = SIGN_GRASS;// место появления гг
        return {heroX, heroY};
    }

    std::pair<int , int> createChest(Map map) {
        int chestX = rand() % map.size;
        int chestY = rand() % map.size;
        while (map.map[chestX * map.size + chestY] == SIGN_FOREST) {
            chestX = rand() % map.size;
            chestY = rand() % map.size;
        }
        map.map[chestX * map.size + chestY] = SIGN_CHEST;// создание сундукa
        return {chestX, chestY};
    }

    void createForest(Map map) {
        int forest = rand() % 700;
        for (int i = 0; i < forest; i++) {
            int x = rand() % map.size;
            int y = rand() % map.size;
            int width = rand() % 100;
            int height = rand() % 100;
            if (height + y < map.size && width + x < map.size)
                for (int width1 = 0; width1 < width; width1++) {
                    for (int long1 = 0; long1 < height; long1++) {
                        map.map[(y + long1) * map.size + x + width1] = SIGN_FOREST;
                    }
                }
            std::cout<< x <<"|"<< y <<"\n";
        }
        for (int width1 = 0; width1 < 20; width1++) {
            for (int long1 = 0; long1 < 20; long1++) {
                map.map[(10 + long1) * map.size + 10 + width1] = SIGN_FOREST;
            }
        }
    }

public:
    mapHero generateMap(int SMap) {
        int *data = new int[SMap * SMap];
        memset(data, 0, sizeof(int) * SMap * SMap);
        srand(time(NULL));
        int x, y, height, width;
        Map map{data, SMap};
        createForest(map);
        auto heroPos = createHero(map);
        auto chestPos = createChest(map);
        mapHero mapHero1;
        mapHero1.heroX = heroPos.first;
        mapHero1.heroY = heroPos.second;
        mapHero1.map = map;
        mapHero1.chestX = chestPos.first;
        mapHero1.chestY = chestPos.second;
        return mapHero1;
    }
};


#endif //CHESTHUNTER_MAPGENERATOR_H
