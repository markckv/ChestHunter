//
// Created by mark on 13.05.18.
//

#ifndef TESTCLIENT_NETSTR_H
#define TESTCLIENT_NETSTR_H

#include <list>
#include <string>
#include <map>
#include "MapHero.h"

class NetStr {public:
    struct game {
        int NP;
int players;
    };
    void send(std::string str, int socket);
    std::string take(int socket);
    std::map<std::string, game> takeGames(int socket);
    int takeInt(int socket);
    void sendInt(int socket, int n);
    mapHero takeMap(int socket);
};


#endif //TESTCLIENT_NETSTR_H
