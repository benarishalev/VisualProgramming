#ifndef LINE_APP
#define LINE_APP

#include "../pointClass/point.hpp"
#include "../nodeClass/node.hpp"
#include <SDL3/SDL.h>
#include <vector>

class Line {
    public:
        int start;
        int end;
    
    Line(int start, int end);
    void Draw(SDL_Renderer* renderer, std::vector<Node> nodes);
};

#endif