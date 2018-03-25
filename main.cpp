#include <iostream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <SDL2/SDL_net.h>
//#include <SDL2/SDL_image.h>
#include <cmath>
#include "SRC/Net.h"
#include "SRC/MapGenerator.h"
#include "SRC/Graphics.h"
#include "SRC/RunGame.h"

#define PI 3.14159265

int ifg = 0;
TCPsocket tspsocket2;

SDL_Window *init(int W, int H) {

    SDL_Window *mainWindow;
    SDL_Init(SDL_INIT_VIDEO);
    // IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    mainWindow = SDL_CreateWindow("chestHunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H,
                                  SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(mainWindow);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    SDL_GL_SetSwapInterval(1);
    SDLNet_Init();
    return mainWindow;
}


using namespace glm;


int main(int argc, char **argv) {
    Net net;
    SDL_Window *window = init(800, 480);
    int isHost = atoi(argv[1]);
    MapGenerator mapGenerator;
    MapGenerator::mapHero mapHero1;
    if (isHost == 0) {
        net.accept(10062);
         mapHero1 = mapGenerator.generateMap(1000);
        //net.sendMap(mapHero1);
    }else{
        net.connect(10062, "127.0.0.1");
        auto map = net.recvMap();
        mapHero1.map = map;
    }



   Graphics graphics;
    graphics.createShaders();

RunGame runGame;
    std::pair<int, int> none;
    runGame.createGLunit2(graphics.createShaders());
    runGame.runGame(mapHero1, none, window, net);


}
