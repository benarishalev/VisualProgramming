#include "line.hpp"

Line::Line(int start, int end, std::string command) {
    this->start = start;
    this->end = end;
    this->command = command;
}

Line::Line(int start, int end) {
    this->start = start;
    this->end = end;
    this->command = "";
}

void Line::Draw(SDL_Renderer* renderer, std::vector<Node> nodes) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // gets the distance and the angle
    // so i can draw the same line but less length
    // so then i can draw the pointer to the nodes
    double angle = getAngle(nodes[this->start].position.x, nodes[this->start].position.y, nodes[this->end].position.x, nodes[this->end].position.y);
    double distance = getDistance(nodes[this->start].position.x, nodes[this->start].position.y, nodes[this->end].position.x, nodes[this->end].position.y);
    Point finalPosition = {(float)(nodes[this->start].position.x + cos(angle) * (distance - 30)), (float)(nodes[this->start].position.y + sin(angle) * (distance - 30))};
    SDL_RenderLine(renderer, nodes[this->start].position.x, nodes[this->start].position.y, finalPosition.x, finalPosition.y);

    // draw rotated pointer to node
    SDL_FRect rect;
    SDL_GetTextureSize(pointerTexture, &rect.w, &rect.h);
    rect.w /= 25;
    rect.h /= 25;
    rect.x = finalPosition.x - rect.w / 2;
    rect.y = finalPosition.y - rect.h / 2;
    SDL_FPoint center = {rect.w / 2, rect.h / 2};
    SDL_RenderTextureRotated(renderer, pointerTexture, NULL, &rect, angle * 180 / PI + 90, &center, SDL_FLIP_NONE);
}

bool Line::operator==(const Line& other) {
    return this->start == other.start && this->end == other.end;
}