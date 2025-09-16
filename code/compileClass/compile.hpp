#ifndef COMPILE_APP
#define COMPILE_APP

#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <variant>

#include "../GLOBALS/globals.hpp"
#include "../variableClass/variable.hpp"

class Compile {
    public:
        std::map<std::string, std::function<void(const std::vector<std::string>&)>> functions;
        std::map<std::string, std::function<std::string(const std::vector<std::string>&)>> actions;
        std::map<std::string, std::function<bool(const std::vector<std::string>&)>> conditions;
        std::map<std::string, Variable>& variables;
    
    Compile(std::map<std::string, Variable>& variables);
    std::string Run(std::string line);
    bool Check(std::string line);
    std::string getActionName(std::string line);
    std::string getFunctionName(std::string line);
    std::string getConditionName(std::string line);
    std::vector<std::string> getArgs(std::string line);
    Variable* getPointer(std::string arg);
    Variable getCopy(std::string arg);
};

#endif