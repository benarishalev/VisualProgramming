#include "line.hpp"

Line::Line(int start, int end) {
    this->start = start;
    this->end = end;
}

void Line::Draw(SDL_Renderer* renderer, std::vector<Node> nodes) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, nodes[this->start].position.x, nodes[this->start].position.y, nodes[this->end].position.x, nodes[this->end].position.y);
}