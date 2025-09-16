#ifndef SCRIPT_APP
#define SCRIPT_APP

#include "../nodeClass/node.hpp"
#include "../lineClass/line.hpp"

#include <vector>
#include <map>
#include <iostream>
#include "../compileClass/compile.hpp"
#include "../variableClass/variable.hpp"
#include "../GLOBALS/globals.hpp"


class Script {
    public:
        std::vector<Node> nodes;
        std::vector<Line> lines;
        std::map<std::string, Variable> variables;

        int index;
        int speed;
        int time;
    
    Script(std::vector<Node> nodes, std::vector<Line> lines, std::map<std::string, Variable> variables);
    void Draw(SDL_Renderer* renderer);

    // void RunAll();
    std::string Run(Compile compile);
};

#endif