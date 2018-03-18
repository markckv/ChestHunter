#include <iostream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <SDL2/SDL_net.h>
//#include <SDL2/SDL_image.h>
#include <cmath>

#define PI 3.14159265
enum GameObject1 {
    SIGN_FOREST = 8,
    SIGN_CHEST = 5,
    SIGN_GRASS = 0
};
struct mapHero {
    int *map;
    int heroX;
    int heroY;
    int chestX;
    int chestY;
};

mapHero generateMap(int SMap) {
    int *map = (int *) SDL_malloc(sizeof(int) * SMap * SMap);
    for (int i = 0; i < SMap; i++) {
        for (int i1 = 0; i1 < SMap; i1++) {
            map[i * SMap + i1] = 0;
        }
    }
    srand(time(NULL));
    int x, y, height, width;
    // созание лесов
    int forest = rand() % 700;
    for (int i = 0; i < forest; i++) {
        x = rand() % 1000;
        y = rand() % 1000;
        width = rand() % 100;
        height = rand() % 100;
        if (height + y < SMap)
            if (width + x < SMap) {
                printf("forest %i %i %i %i", y, x, width, height);
                for (int width1 = 0; width1 < width; width1++) {
                    for (int long1 = 0; long1 < height; long1++) {
                        map[(x + width1) * SMap + y + long1] = SIGN_FOREST;
                    }
                }
            }

    }
    //проверка что гг будет не в лесу
    int heroX, heroY;
    heroX = rand() % 1000;
    heroY = rand() % 1000;
    while (map[heroX * SMap + heroY] == SIGN_FOREST) {
        heroX = rand() % 1000;
        heroY = rand() % 1000;
    }
    map[heroX * SMap + heroY] = SIGN_GRASS;// место появления гг
    printf("forest");
    //проверка что сундук будет не в лесу
    int chestX = rand() % 1000;
    int chestY = rand() % 1000;
    while (map[chestX * SMap + chestY] == SIGN_FOREST) {
        chestX = rand() % 1000;
        chestY = rand() % 1000;
    }
    map[chestX * SMap + chestY] = SIGN_CHEST;// создание сундука

    mapHero mapHero1;
    mapHero1.heroX = heroX;
    mapHero1.heroY = heroY;
    mapHero1.map = map;
    mapHero1.chestX = chestX;
    mapHero1.chestY = chestY;
    return mapHero1;

}

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
    return mainWindow;
}

int data[2];

GLuint createShader(const GLchar *gLchar, GLenum gLenum) {
    GLuint gLuint = glCreateShader(gLenum);
    glShaderSource(gLuint, 1, &gLchar, nullptr);
    glCompileShader(gLuint);
    GLint ok;
    glGetShaderiv(gLuint, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLchar log[512];
        glGetShaderInfoLog(gLuint, 512, nullptr, log);
        printf("%s", log);
    }
    return gLuint;
}

int sentNet(int camx, int camz) {
    int ss[] = {camx, camz};
    SDLNet_TCP_Send(tspsocket2, ss, sizeof(int) * 2);


}

int *netrecv() {


    int f = SDLNet_TCP_Recv(tspsocket2, data, sizeof(int) * 2);

    //      return data;
}

using namespace glm;

void addVec3(std::vector<GLfloat> &out, vec3 vec) {
    out.push_back(vec.x);
    out.push_back(vec.y);
    out.push_back(vec.z);
}

void generateQuad(std::vector<GLfloat> &out, vec3 bl, vec3 br, vec3 ul, vec3 ur, vec3 color) {
    //First triangle
    addVec3(out, bl);
    addVec3(out, color);
    addVec3(out, ul);
    addVec3(out, color);
    addVec3(out, ur);
    addVec3(out, color);
    //Second triangle
    addVec3(out, bl);
    addVec3(out, color);
    addVec3(out, br);
    addVec3(out, color);
    addVec3(out, ur);
    addVec3(out, color);
}

void generateCube(std::vector<GLfloat> &out, glm::vec3 leftBottom, float lenght, float width, float height) {
    vec3 dbl = leftBottom;
    vec3 dul = leftBottom + vec3(0, 0, height);
    vec3 dbr = dbl + vec3(lenght, 0, 0);
    vec3 dur = dbl + vec3(lenght, 0, height);
    vec3 ubl = dbl + vec3(0, width, 0);
    vec3 uul = dul + vec3(0, width, 0);
    vec3 ubr = dbr + vec3(0, width, 0);
    vec3 uur = dur + vec3(0, width, 0);

    generateQuad(out, dbl, dbr, dul, dur, vec3(1, 0, 0));
    generateQuad(out, ubl, ubr, uul, uur, vec3(0, 1, 0));
    generateQuad(out, dbl, dbr, ubl, ubr, vec3(0, 0, 1));
    generateQuad(out, dul, dur, uul, uur, vec3(1, 0, 1));
    generateQuad(out, dbl, dul, ubl, uul, vec3(1, 1, 0));
    generateQuad(out, dbr, dur, ubr, uur, vec3(0, 1, 1));

}

int main(int argc, char **argv) {
    int argvInt = atoi(argv[1]);
    if (argvInt == 0) {
        SDLNet_Init();
        IPaddress address;
        SDLNet_ResolveHost(&address, nullptr, 10003);
        TCPsocket tspsocket = SDLNet_TCP_Open(&address);
        data[0] = 3;
        data[1] = 3;
        tspsocket2 = nullptr;
        while (tspsocket2 == nullptr) {
            tspsocket2 = SDLNet_TCP_Accept(tspsocket);
        }
    }
    if (argvInt == 1) {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDLNet_Init();
        IPaddress address;
        if (SDLNet_ResolveHost(&address, "127.0.0.1", 10003)) {
            printf("n");
        }
        tspsocket2 = nullptr;
        while (tspsocket2 == nullptr)
            tspsocket2 = SDLNet_TCP_Open(&address);
    }

    mapHero mapHero1 = generateMap(1000);
    SDL_Window *window = init(800, 480);

    auto *pfGPU = const_cast<GLchar *>("#version 300 es \n"
            "uniform mat4 projection_view;\n"
            "uniform int startid;\n"
            "layout (location = 0) in vec3 v3; \n"
            "layout (location = 1) in vec3 c; \n"
            "out vec4 colorForFragment; \n"
            "void main(){ \n"
            "int arrSize = 100;\n"
//                "float xTrans = 2.0f* float((gl_InstanceID+startid) % arrSize - arrSize/2);\n"
//                "float yTrans = 2.0f* float(((gl_InstanceID+startid) / arrSize) % arrSize );\n"
//                "float zTrans = 2.0f* float(((gl_InstanceID+startid) / arrSize) / arrSize );\n"
            "gl_Position = projection_view * (vec4(v3, 1.0));\n"
            "colorForFragment = vec4(c, 1.0f);\n"
            "}\0");
    auto *fragmentGPU = const_cast<GLchar *>("#version 300 es \n"
            "precision mediump float ; \n"
            "in vec4 colorForFragment;\n"
            "out vec4 color; \n"
            "void main (){"
            "color = colorForFragment;\n"
            "}\0");
    GLuint gLuint = createShader(pfGPU, GL_VERTEX_SHADER);
    GLuint gLuint1 = createShader(fragmentGPU, GL_FRAGMENT_SHADER);
    GLuint gLuint2 = glCreateProgram();
    glAttachShader(gLuint2, gLuint);
    glAttachShader(gLuint2, gLuint1);
    GLint gLint;
    glLinkProgram(gLuint2);
    glGetProgramiv(gLuint2, GL_LINK_STATUS, &gLint);
    if (!gLint) {
        GLchar gLchar[512];
        glGetProgramInfoLog(gLuint2, 512, nullptr, gLchar);

        printf("%s", gLchar);
    }

    std::vector<GLfloat> vertexes;
    generateCube(vertexes, vec3(-10, -10, -10), 20, 20, 20);
    generateCube(vertexes, vec3(-10, -0.5, -10), 20, 1, 20);
    generateCube(vertexes, vec3(-10, -2.5, -10), 20, 5, 20);
    //generateQuad(vertexes, vec3(0,0,0), vec3(1,0,0), vec3(0,1,0), vec3(1,1,0), vec3(1,1,1));
//    int arrSize = 30;
//    for (int x = -arrSize; x < arrSize; x++) {
//        for (int y = -arrSize; y < arrSize; y++) {
//            for (int z = -arrSize; z < arrSize; z++) {
//                generateCube(vertexes, vec3(x+0.5*x,y+0.5*y,z+0.5*z), 1, 1, 1);
//            }
//        }
//    }

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid *) (3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glClearColor(0.2, 0.3, 0.3, 1.0);

    glm::mat4 transform;
    glm::mat4 endTransform;
    GLuint transformGPULoc = glGetUniformLocation(gLuint2, "projection_view");
    GLuint transformGPULoc2 = glGetUniformLocation(gLuint2, "startid");

    glUseProgram(gLuint2);
    int down = SDLK_w;
    int up = SDLK_s;
    int left = SDLK_a;
    int right = SDLK_d;
    int q = SDLK_q;
    int e = SDLK_e;
    int upup = SDLK_KP_PLUS;
    int downdown = SDLK_KP_MINUS;
    float cameraX = 0;
    float cameray = 10;
    float cameraz = 0; int oldangle = 0;

    int s = 0;
    int *netHero;
    int angle = 90;
    double cameraVX = 0;
    double cameraVY = 0;
    int plaerN = 1;
    while (true) {
        SDL_Event event;
        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN)
                s = event.key.keysym.sym;
            if (event.type == SDL_KEYUP)
                s = 0;
        }
        if (s == q) {

            angle = angle - 1;

        }
        if (s == e) {
            angle = angle + 1;

        }
        if (angle > 360) {
            angle = 1;
        }
        if (angle < 0) {
            angle = 360;
        }
        if (s == left) {
            oldangle = angle;
            angle = angle+90;
            if(angle> 360){
                angle = 0 +angle;
            }
            if (mapHero1.map[int(cameraX - cos(angle * PI / 180) * 2) * 1000 + int(cameraz - sin(angle * PI / 180) * 2)] != SIGN_FOREST) {

                cameraz = cameraz - sin(angle * PI / 180) * 2;
                cameraX = cameraX - cos(angle * PI / 180) * 2;
            }
            angle = oldangle;
        }
        if (s == right) {
            oldangle = angle;
            angle = angle-90;
            if(angle< 0){
                angle = 360 +angle;
            }
            if (mapHero1.map[int(cameraX - cos(angle * PI / 180) * 2) * 1000 + int(cameraz - sin(angle * PI / 180) * 2)] != SIGN_FOREST) {
            cameraz = cameraz - sin(angle * PI / 180) * 2;
            cameraX =  cameraX - cos(angle * PI / 180) * 2;}
            angle = oldangle;
        }
        if (s == up) {
            if (mapHero1.map[int(cameraX - cos(angle * PI / 180) * 2) * 1000 + int(cameraz - sin(angle * PI / 180) * 2)] != SIGN_FOREST) {
            cameraz = cameraz - sin(angle * PI / 180) * 2;
            cameraX =  cameraX - cos(angle * PI / 180) * 2;}
        }
        if (s == down) {
            oldangle = angle;
            angle = angle-180;
            if(angle< 0){
                angle = 360 +angle;
            }
            if (mapHero1.map[int(cameraX - cos(angle * PI / 180) * 2) * 1000 + int(cameraz - sin(angle * PI / 180) * 2)] != SIGN_FOREST) {
            cameraz = cameraz - sin(angle * PI / 180) * 2;
            cameraX =  cameraX - cos(angle * PI / 180) * 2;}
            angle = oldangle;
        }
//        if (s == downdown) {
//            cameraX = cameraX - 20;
//        }
//        if (s == upup) {
//            cameraX = cameraX + 20;
//        }
        if (plaerN > 0) {
            if (argvInt == 0) {
                sentNet(cameraX / 20, cameraz / 20);
                netrecv();
            }
            if (argvInt == 1) {
                netrecv();
                sentNet(cameraX / 20, cameraz / 20);
            }
        }
        size_t start = SDL_GetTicks();
        cameraVY = sin(angle * PI / 180) * 2;
        cameraVX = cos(angle * PI / 180) * 2;
        // transform = glm::rotate(transform, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

        glm::mat4 view = glm::lookAt(glm::vec3(cameraX, cameray, cameraz),
                                     glm::vec3(cameraX + cameraVX, cameray, cameraz + cameraVY), glm::vec3(0, 1, 0));

        SDL_Event e{};
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT:
                exit(0);
            default:
                break;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = (cameraX / 20) - 20; i < (cameraX / 20) + 20; i++)
            for (int i1 = (cameraz / 20) - 20; i1 < (cameraz / 20) + 20; i1++) {
                if (i < 0 || i1 < 0 || i1 >= 1000 || i >= 1000)
                    continue;
                mat4 move;
                move = glm::translate(move, vec3(i * 20, 0, i1 * 20));
                endTransform = projection * view * transform * move;
                glUniformMatrix4fv(transformGPULoc, 1, GL_FALSE, value_ptr(endTransform));
                if (mapHero1.map[i * 1000 + i1] == SIGN_GRASS) {
                    glDrawArrays(GL_TRIANGLES, 6 * 2 * 3, 6 * 2 * 3);
                }
                if (mapHero1.map[i * 1000 + i1] == SIGN_FOREST) {
                       glDrawArrays(GL_TRIANGLES,0, 6*2*3);
                }
                if (mapHero1.map[i * 1000 + i1] == SIGN_CHEST) {
                    glDrawArrays(GL_TRIANGLES, 6 * 2 * 3 * 2, 6 * 2 * 3);
                }
                if (plaerN > 0) {
                    if (i == data[0] && i1 == data[1])
                        glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
                }
            };

        SDL_GL_SwapWindow(window);

        size_t end = SDL_GetTicks();
        std::cout << "x: " << cameraX / 20 << std::endl;
        std::cout << "y(z): " << cameraz / 20 << std::endl;
        //    std::cout << "Delay: " << end-start << std::endl;

//        SDL_Delay(200);
    }
}
