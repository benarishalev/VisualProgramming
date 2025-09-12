#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "scriptClass/script.hpp"
#include "compileClass/compile.hpp"
#include "variableClass/variable.hpp"
#include "globals.hpp"

std::vector<Variable> registers = std::vector<Variable>(10);
int WIDTH = 1000;
int HEIGHT = 1000;


int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "direct3d");
    SDL_Window* window = SDL_CreateWindow("Programming", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

    // load images
    SDL_Texture* circleImg = IMG_LoadTexture(renderer, "imgs/circle.png");

    // first script
    std::vector<Node> nodes = {
        Node(Point(30, 30), ""),
        Node(Point(100, 200), "mov r0, 1"),
        Node(Point(100, 300), "mov r1, 1"),

        Node(Point(200, 400), "mov r2, r0"),
        Node(Point(200, 500), "add r0, r1"),
        Node(Point(300, 500), "mov r1, r2"),
        Node(Point(300, 400), "call print, 1"),
    };
    std::vector<Line> lines = {
        Line(0, 1),
        Line(1, 2),
        Line(2, 3),

        Line(3, 4),
        Line(4, 5),
        Line(5, 6),
        Line(6, 3),
    };
    std::map<std::string, Variable> variables;
    Script script(nodes, lines, variables);
    Compile compile(script.variables);

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        script.Run(compile);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        script.Draw(renderer, circleImg);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}