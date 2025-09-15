#include "globals.hpp"

std::vector<Variable> registers = std::vector<Variable>(10);
int WIDTH = 1000;
int HEIGHT = 1000;

double PI = 3.14159265358979323846;

double getDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double getAngle(double x1, double y1, double x2, double y2) {
    return atan2(y2 - y1, x2 - x1);
}

SDL_Cursor* regularCursor = nullptr;
SDL_Cursor* handCursor = nullptr;

SDL_Texture* pointerTexture = nullptr;
SDL_Texture* circleImg = nullptr;

