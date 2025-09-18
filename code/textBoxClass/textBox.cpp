#include "textBox.hpp"

TextBox::TextBox(std::string text, SDL_Renderer* renderer) : text(text) {
    this->setDefualtTexture(renderer, codeFont, "DEFUALT");
}
TextBox::TextBox() {}

void TextBox::setDefualtTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), 0, {255, 255, 255});
    if (!surface) {
        std::cout << "error" << SDL_GetError() << std::endl;
        return;
    }
    this->defualtTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}


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
    // get the defualt width
    SDL_FRect defualtRect;
    SDL_GetTextureSize(this->defualtTexture, &defualtRect.w, &defualtRect.h);
    
    // get the text width
    SDL_FRect textRect;
    SDL_FRect rect;
    SDL_GetTextureSize(this->texture, &textRect.w, &textRect.h);
    textRect.x = x - textRect.w / 2;
    textRect.y = y;
    rect.w = std::max(textRect.w, defualtRect.w);
    rect.h = defualtRect.h;
    rect.x = x - rect.w / 2;
    rect.y = y;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &rect);
    if (this->text.size() > 0) {
        SDL_RenderTexture(renderer, this->texture, nullptr, &textRect);
    }
}

void TextBox::handleInput(char input) {
    if (input == '\0') {if (this->text.size() > 0) {this->text.pop_back();} return;}
    this->text += input;
}