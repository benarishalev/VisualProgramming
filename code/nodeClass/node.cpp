#include "node.hpp"

Node::Node(Point position, std::string command) {
    this->position = position;
    this->command = command;
    this->size = 25;
}

Node::Node(Point position) {
    this->position = position;
    this->command = "";
    this->size = 25;
}

void Node::Draw(SDL_Renderer* renderer, SDL_Texture* circleImg) {
    SDL_FRect rect;
    rect.w = this->size;
    rect.h = this->size;
    rect.x = this->position.x - this->size / 2;
    rect.y = this->position.y - this->size / 2;
    SDL_RenderTexture(renderer, circleImg, NULL, &rect);
}