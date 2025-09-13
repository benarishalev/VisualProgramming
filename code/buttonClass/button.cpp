#include "button.hpp"

Button::Button(Point position, Point size)
    : position(position), size(size) {}

Button::Button(Point position, Point size, std::string text, SDL_Renderer* renderer, TTF_Font* font) : position(position), size(size) {
    setText(renderer, text, font);
}

Button::Button() : position({0, 0}), size({0, 0}) {}

void Button::Draw(SDL_Renderer* renderer, SDL_Color color) {
    SDL_FRect rect = {position.x, position.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &rect);

    SDL_FRect textRect;
    SDL_GetTextureSize(texture, &textRect.w, &textRect.h);
    textRect.w *= 2;
    textRect.h *= 2;
    textRect.x = position.x + (size.x - textRect.w) / 2;
    textRect.y = position.y + (size.y - textRect.h) / 2;
    SDL_RenderTexture(renderer, texture, NULL, &textRect);
}

void Button::setText(SDL_Renderer* renderer, std::string text, TTF_Font*& font) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_NEAREST);
}

bool Button::isClick(int x, int y) {
    return x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y;
}