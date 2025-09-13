#ifndef BUTTON_APP
#define BUTTON_APP

#include "../pointClass/point.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Button {
    public:
        Point position;
        Point size;
        SDL_Texture* texture;
    
    Button(Point position, Point size);
    Button(Point position, Point size, std::string text, SDL_Renderer* renderer, TTF_Font* font);
    Button();
    Button operator=(const Button& other) {
        this->position = other.position;
        this->size = other.size;
        this->texture = other.texture;
        return *this;
    }

    bool isClick(int x, int y);
    void Draw(SDL_Renderer* renderer, SDL_Color color);
    void setText(SDL_Renderer* renderer, std::string text, TTF_Font*& font);
};

#endif