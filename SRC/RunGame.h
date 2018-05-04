//
// Created by mark on 25.03.18.
//

#ifndef CHESTHUNTER_CONTROL_H
#define CHESTHUNTER_CONTROL_H

#define PI 3.14159265

#include "Net.h"
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLES2/gl2.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "GameObject.h"
#include "MapGenerator.h"
#include "graphics/Drawer.h"
#include "graphics/ShaderProgram.h"

using namespace glm;

class RunGame {
    ShaderProgram gLuint2;
public:
    void createGLunit2(ShaderProgram gLuint) {
        gLuint2 = gLuint;
    }

    void runGame(MapGenerator::mapHero mapHero1, std::pair<int, int> data, SDL_Window *window, Net net) {
        glm::mat4 transform;
        glm::mat4 endTransform;
        Drawer drawer;
        GLuint lightP = glGetUniformLocation(gLuint2, "lightP");
        GLuint lightC = glGetUniformLocation(gLuint2, "lightC");
        GLuint moveMat = glGetUniformLocation(gLuint2 ,  "transform");
        glUniform3f(lightP,100,501,100 );
        glUniform3f(lightC,0.3,0.3,0.3);
        GLuint transformGPULoc = glGetUniformLocation(gLuint2, "projection_view");
        GLuint transformGPULoc2 = glGetUniformLocation(gLuint2, "startid");
        GameObject1 gameObject1;
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
        float cameraz = 0;
        int oldangle = 0;

        int s = 0;
        int *netHero;
        int angle = 90;
        double cameraVX = 0;
        double cameraVY = 0;
        int plaerN = 1;
        while (true) {
            SDL_PumpEvents();
            auto keyBoard = SDL_GetKeyboardState(nullptr);
            if (keyBoard[SDL_SCANCODE_Q]) {

                angle = angle - 1;

            }
            if (keyBoard[SDL_SCANCODE_E]) {
                angle = angle + 1;

            }
//            if (angle > 360) {
//                angle = 1;
//            }
//            if (angle < 0) {
//                angle = 360;
//            }
            if (keyBoard[SDL_SCANCODE_A]) {
                oldangle = angle;
                angle = angle + 90;
                if (angle > 360) {
                    angle = 0 + angle;
                }
                if (mapHero1.map.map[int(cameraX/20 - cos(angle * PI / 180) * 0.1) * mapHero1.map.size +
                                     int(cameraz/20  - sin(angle * PI / 180) * 0.1)] != SIGN_FOREST) {

                    cameraz = cameraz - sin(angle * PI / 180) * 2;
                    cameraX = cameraX - cos(angle * PI / 180) * 2;
                }
                angle = oldangle;
            }
            if (keyBoard[SDL_SCANCODE_D]) {
                oldangle = angle;
                angle = angle - 90;
                if (angle < 0) {
                    angle = 360 + angle;
                }
                if (mapHero1.map.map[int(cameraX/20 - cos(angle * PI / 180) * 0.1) * mapHero1.map.size +
                                     int(cameraz/20 - sin(angle * PI / 180) * 0.1)] != SIGN_FOREST) {
                    cameraz = cameraz - sin(angle * PI / 180) * 2;
                    cameraX = cameraX - cos(angle * PI / 180) * 2;
                }
                angle = oldangle;
            }
            if (keyBoard[SDL_SCANCODE_S]) {
                if (mapHero1.map.map[int(cameraX/20 - cos(angle * PI / 180) * 0.1) * mapHero1.map.size +
                                     int(cameraz/20 - sin(angle * PI / 180) * 0.1)] != SIGN_FOREST) {
                    cameraz = cameraz - sin(angle * PI / 180) * 2;
                    cameraX = cameraX - cos(angle * PI / 180) * 2;
                }
            }
            if (keyBoard[SDL_SCANCODE_W]) {
                oldangle = angle;
                angle = angle - 180;
                if (angle < 0) {
                    angle = 360 + angle;
                }
                if (mapHero1.map.map[int(cameraX/20 - cos(angle * PI / 180) * 0.1) * mapHero1.map.size +
                                     int(cameraz/20 - sin(angle * PI / 180) * 0.1)] != SIGN_FOREST) {
                    cameraz = cameraz - sin(angle * PI / 180) * 2;
                    cameraX = cameraX - cos(angle * PI / 180) * 2;
                }
                angle = oldangle;
            }
            if (plaerN > 0) {
//                net.send(cameraX / 20, cameraz / 20);
//                data = net.recieve();
data = {0,0};
            }

            size_t start = SDL_GetTicks();
            cameraVY = sin(angle * PI / 180) * 2;
            cameraVX = cos(angle * PI / 180) * 2;
            // transform = glm::rotate(transform, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 projection = glm::perspective(1.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

            glm::mat4 view = glm::lookAt(glm::vec3(cameraX, cameray, cameraz),
                                         glm::vec3(cameraX + cameraVX, cameray, cameraz + cameraVY),
                                         glm::vec3(0, 1, 0));

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
                    if (i < 0 || i1 < 0 || i1 >= mapHero1.map.size || i >= mapHero1.map.size)
                        continue;
                    mat4 move;
                    move = glm::translate(move, vec3(i * 20, 0, i1 * 20));
                    mat4 endTransform = projection * view * transform * move;
                    glUniformMatrix4fv(transformGPULoc, 1, GL_FALSE, glm::value_ptr(endTransform));
                    glUniformMatrix4fv(moveMat,1, GL_FALSE, glm::value_ptr(move));
                    switch(mapHero1.map.map[i * mapHero1.map.size + i1]){
                        case SIGN_GRASS:
                            drawer.draw("GRASS");
                            break;
                        case SIGN_FOREST:
                    if(((i+i1) % 5) == 1){
                        drawer.draw("FOREST2");
                    }
                            if(((i+i1) % 5) == 2){
                                drawer.draw("FOREST");
                            }
                            if(((i+i1) % 5) == 3){
                                drawer.draw("FOREST3");
                            }
                            if(((i+i1) % 5) == 4){
                               drawer.draw("FOREST4");
                            }
                            drawer.draw("GRASS");

                            break;
                        case SIGN_CHEST:
                            drawer.draw("GRASS");
                            drawer.draw("CHEST");
                            break;
                        default:
                            throw std::logic_error("i don't know cell");
                    }

                    if (plaerN > 0) {
                        if (i == data.first && i1 == data.second)
                            drawer.draw("HERO");
                    }

                };

            SDL_GL_SwapWindow(window);
            std::cout << cameraX/20 <<"|"<< cameraz/20<<"\n";
            size_t end = SDL_GetTicks();

            //    std::cout << "Delay: " << end-start << std::endl;

            //        SDL_Delay(200);
        }
    }
};


#endif //CHESTHUNTER_CONTROL_H
