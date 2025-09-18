#ifndef TEXT_BOX_APP
#define TEXT_BOX_APP

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <algorithm>

#include "../GLOBALS/globals.hpp"

class TextBox {
    public:
        std::string text;
        SDL_Texture* texture;
        // using defulat texture so i can set the size normally
        SDL_Texture* defualtTexture;

    TextBox(std::string text, SDL_Renderer* renderer);
    TextBox();
    void setDefualtTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text);
    void setTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
    void Draw(SDL_Renderer* renderer, int x, int y);
    void handleInput(char input);
};

#endif