//
// Created by mark on 13.05.18.
//

#include <zconf.h>
#include "NetStr.h"
void NetStr::send(std::string str, int socket) {
    int size = str.size()+1;
    write(socket, &size, sizeof(int));
  write(socket, str.c_str(), size);

}

std::string NetStr::take(int socket) {
    int size;
    read(socket,& size, sizeof(int));
    char *str2 = new char[size];
    read(socket,str2, size);
    std::string str (str2);
    return str;
}

int NetStr::takeInt(int socket) {
    int n;
    read(socket, &n, sizeof(int));
    return n;
}

void NetStr::sendInt(int socket, int n) {
    write(socket, &n, sizeof(int));

}

std::map<std::string, NetStr::game> NetStr::takeGames(int socket) {
    int size = takeInt(socket);
    std::map<std::string, NetStr::game> games;
    for(int i =0; i<size; i++){
        std::string name = take(socket);
        int now  = takeInt(socket);
        int NP = takeInt(socket);
        games[name] = game{NP, now};
    }
    return games;
}

mapHero NetStr::takeMap(int socket) {
    mapHero mapHero1;
    mapHero1.map.size = takeInt(socket);
    int *map = new int[mapHero1.map.size *mapHero1.map.size  ];
    mapHero1.map.map = map;
    for(int x = 0; x < mapHero1.map.size; x++)
        for(int y = 0; y < mapHero1.map.size;y++){
            mapHero1.map.map[y*mapHero1.map.size + x] =  takeInt(socket);
        }

    return mapHero1;
}
//  void NetStr::sendGames(int socket, std::map<std::string, Dispatcher::game> games) {
//    sendInt(socket, games.size());
//    for(auto it = games.begin(); it != games.end(); it++) {
//        send(it->first, socket);
//        sendInt(socket, it->second.players.size() );
//        sendInt(socket, it->second.NP);
//    }
