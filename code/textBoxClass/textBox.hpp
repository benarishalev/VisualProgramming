#ifndef TEXT_BOX_APP
#define TEXT_BOX_APP

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <algorithm>

class TextBox {
    public:
        std::string text;
        SDL_Texture* texture;

    TextBox(std::string text);
    TextBox();
    void setTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
    void Draw(SDL_Renderer* renderer, int x, int y);
    void handleInput(char input);
};

#endif