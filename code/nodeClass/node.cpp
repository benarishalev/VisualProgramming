#include "node.hpp"

Node::Node(Point position, std::string command) {
    this->position = position;
    this->command = command;
    this->size = 25;
    this->isOn = false;
}

void Node::Draw(SDL_Renderer* renderer, SDL_Texture* circleImg) {
    SDL_FRect rect;
    rect.w = this->size;
    rect.h = this->size;
    rect.x = this->position.x - this->size / 2;
    rect.y = this->position.y - this->size / 2;
    if (this->isOn) {
        this->size = 35;
        SDL_SetTextureColorMod(circleImg, 255, 0, 0);
    } else {
        this->size = 25;
        SDL_SetTextureColorMod(circleImg, 255, 255, 255);
    }
    SDL_RenderTexture(renderer, circleImg, NULL, &rect);
}