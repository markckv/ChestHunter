#include <iostream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <SDL2/SDL_net.h>
//#include <SDL2/SDL_image.h>
#include <cmath>
#include <SDL_opengles2_gl2.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "SRC/Net.h"
#include "../CLionProjects/GameServer/MapGenerator.h"
#include "SRC/Graphics.h"
#include "SRC/RunGame.h"
#include "SRC/NetStr.h"
#include "SRC/MapHero.h"

int ifg = 0;
TCPsocket tspsocket2;
//std::list<int> & listSocket;
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
    int port;
    port = std::stoi(argv[1]);
    int  acceptSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    hostent *hostent1 = gethostbyname(argv[2]);
    bcopy((char *)hostent1->h_addr, (char *)&serv_addr.sin_addr.s_addr, hostent1->h_length);
    int connect1 = connect(acceptSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    perror("");
mapHero maphero;
NetStr netStr;
    int NP;

    Net net;
    SDL_Window *window = init(1280, 720);
    Graphics graphics;

RunGame runGame;
    std::pair<int, int> none;
    runGame.createGLunit2(graphics.createShaders());
    runGame.runGame(acceptSocket, window);


}
