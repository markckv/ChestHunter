//
// Created by mark on 18.03.18.
//

#ifndef CHESTHUNTER_NET_H
#define CHESTHUNTER_NET_H
#include <string>
#include <SDL2/SDL_net.h>
#include "../../CLionProjects/GameServer/MapGenerator.h"


class Net {
    TCPsocket tspsocket ;
    TCPsocket tspsocket2 ;
public:
    void sendMap(MapGenerator::mapHero mapHero){
        SDLNet_TCP_Send(tspsocket2, &mapHero.map.size , sizeof(int));
        SDLNet_TCP_Send(tspsocket2, mapHero.map.map , sizeof(int)*mapHero.map.size* mapHero.map.size);
    }
    MapGenerator::Map recvMap(){
        MapGenerator::Map map;
        SDLNet_TCP_Recv(tspsocket2, &map.size , sizeof(int) );
        map.map = new int[map.size*map.size];
        SDLNet_TCP_Recv(tspsocket2,map.map , sizeof(int) *map.size * map.size);
        return map;

    }
    void connect(int port, std::string ip ){
        SDL_Init(SDL_INIT_EVERYTHING);
        SDLNet_Init();
        IPaddress address;
        SDLNet_ResolveHost(&address, ip.c_str() , port);
        tspsocket2 = nullptr;
        while (tspsocket2 == nullptr)
            tspsocket2 = SDLNet_TCP_Open(&address);
}


    void accept(int port){
        IPaddress address;
        SDLNet_ResolveHost(&address, nullptr, port);
        tspsocket = SDLNet_TCP_Open(&address);
        tspsocket2 = nullptr;
        while (tspsocket2 == nullptr) {
            tspsocket2 = SDLNet_TCP_Accept(tspsocket);
        }
    }
    void send(int x, int y){
        int data[] = {x, y};
        SDLNet_TCP_Send(tspsocket2, data, sizeof(int) * 2);
    }
    std::pair<int , int > recieve(){
        int data[2];
        SDLNet_TCP_Recv(tspsocket2, data, sizeof(int) * 2);
        return std::pair<int , int >(data[0], data [1]);
    }
};



#endif //CHESTHUNTER_NET_H
