#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <cmath>

#include "../variableClass/variable.hpp"

extern std::vector<Variable> registers;
extern int WIDTH;
extern int HEIGHT;

double getDistance(double x1, double y1, double x2, double y2);

extern SDL_Cursor* regularCursor;
extern SDL_Cursor* handCursor;