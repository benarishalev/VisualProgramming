#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <cmath>

#include "../variableClass/variable.hpp"
#include "../pointClass/point.hpp"

extern std::vector<Variable> registers;
extern int WIDTH;
extern int HEIGHT;

extern double PI;

double getDistance(double x1, double y1, double x2, double y2);
double getAngle(double x1, double y1, double x2, double y2);

extern SDL_Cursor* regularCursor;
extern SDL_Cursor* handCursor;

extern SDL_Texture* circleImg;
extern SDL_Texture* pointerTexture;