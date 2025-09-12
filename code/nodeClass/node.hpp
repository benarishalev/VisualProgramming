#ifndef NODE_APP
#define NODE_APP

#include "../pointClass/point.hpp"
#include <string>
#include "SDL3_image/SDL_image.h"

class Node {
    public:
        Point position;
        std::string command;
        float size;
        bool isOn;
    
    Node(Point position, std::string command);
    void Draw(SDL_Renderer* renderer, SDL_Texture* circleImg);
};

#endif