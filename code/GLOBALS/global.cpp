#include "globals.hpp"

std::vector<Variable> registers = std::vector<Variable>(10);
int WIDTH = 1000;
int HEIGHT = 1000;

double getDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

SDL_Cursor* regularCursor = nullptr;
SDL_Cursor* handCursor = nullptr;

