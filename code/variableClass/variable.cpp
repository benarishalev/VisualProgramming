#include "variable.hpp"

Variable::Variable(std::string value, char type) : value(value), type(type) {}
Variable::Variable() : value("0"), type('i') {}