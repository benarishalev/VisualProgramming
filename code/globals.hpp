#pragma once

#include <string>
#include <vector>
#include "variableClass/variable.hpp"

extern std::vector<Variable> registers;
extern int WIDTH;
extern int HEIGHT;

double getDistance(double x1, double y1, double x2, double y2);