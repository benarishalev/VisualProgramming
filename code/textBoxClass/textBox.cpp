#include "textBox.hpp"

TextBox::TextBox(std::string text) : text(text) {}
TextBox::TextBox() {}

void TextBox::setTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, this->text.c_str(), 0, color);
    if (!surface) {
        // i dont want to print anything because if the text width is zero
        // it gives unneccery "error"
        return;
    }
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

void TextBox::Draw(SDL_Renderer* renderer, int x, int y) {
    SDL_FRect rect;
    SDL_GetTextureSize(this->texture, &rect.w, &rect.h);
    rect.w *= 2;
    rect.h *= 2;
    rect.x = x;
    rect.y = y;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &rect);
    if (this->text.size() > 0) {
        SDL_RenderTexture(renderer, this->texture, nullptr, &rect);
    }
}

void TextBox::handleInput(char input) {
    if (input == '\0') {if (this->text.size() > 0) {this->text.pop_back();} return;}
    this->text += input;
}