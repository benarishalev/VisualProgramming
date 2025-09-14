#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <cmath>

#include "scriptClass/script.hpp"
#include "compileClass/compile.hpp"
#include "variableClass/variable.hpp"
#include "placementClass/placement.hpp"
#include "GLOBALS/globals.hpp"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "direct3d");
    SDL_Window* window = SDL_CreateWindow("Programming", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

    SDL_StartTextInput(window);

    // set up the cursor
    regularCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
    handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    SDL_SetCursor(regularCursor);

    TTF_Font* font = TTF_OpenFont("fonts/pixel.ttf", 20);

    // load images
    SDL_Texture* circleImg = IMG_LoadTexture(renderer, "imgs/circle.png");

    // fib function
    // std::vector<Node> nodes = {
    //     Node(Point(30, 30), ""),
    //     Node(Point(100, 200), "mov r0, 1"),
    //     Node(Point(100, 300), "mov r1, 1"),

    //     Node(Point(200, 400), "mov r2, r0"),
    //     Node(Point(200, 500), "add r0, r1"),
    //     Node(Point(300, 500), "mov r1, r2"),
    //     Node(Point(300, 400), "call print, 1"),
    // };

    std::vector<Node> nodes = {
        Node({100, 100}),
    };
    std::vector<Line> lines = {
        
    };
    std::map<std::string, Variable> variables;
    Script script(nodes, lines, variables);
    Compile compile(script.variables);
    Placement placement(renderer, font, WIDTH, HEIGHT);

    SDL_Event event;
    bool running = true;

    bool scriptRunning = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (placement.ClickDialog(script, event.button.x, event.button.y, renderer, font)) {
                        continue;
                    }
                    if (placement.Click(event.button.x, event.button.y)) {
                        continue;
                    }
                    placement.PlaceNode(script, event.button.x, event.button.y);
                    placement.PlaceLine(script, event.button.x, event.button.y);
                    placement.moveNode(script, event.button.x, event.button.y);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    placement.openDialog(script, event.button.x, event.button.y);
                }
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                WIDTH = event.window.data1;
                HEIGHT = event.window.data2;
                placement.updatePosition(WIDTH, HEIGHT);
            }
            if (event.type == SDL_EVENT_TEXT_INPUT) {
                placement.getInput(script, event.text.text[0], renderer, font);
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_BACKSPACE) {
                    placement.getInput(script, '\0', renderer, font);
                }
            }
        }

        script.Run(compile);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        script.Draw(renderer, circleImg);
        placement.Draw(renderer);
        placement.moveNodeUpdate(script);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}