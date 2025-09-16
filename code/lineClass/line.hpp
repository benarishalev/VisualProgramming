#ifndef LINE_APP
#define LINE_APP

#include "../pointClass/point.hpp"
#include "../nodeClass/node.hpp"
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include "../GLOBALS/globals.hpp"
#include <algorithm>

class Line {
    public:
        int start;
        int end;
        std::string command;
        float lengthPercentage;
    
    Line(int start, int end, std::string command);
    Line(int start, int end); // "defualt" constructor
    void Draw(SDL_Renderer* renderer, std::vector<Node> nodes);
    bool operator==(const Line& other);
};

#endif