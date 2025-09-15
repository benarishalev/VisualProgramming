#include "script.hpp"

Script::Script(std::vector<Node> nodes, std::vector<Line> lines, std::map<std::string, Variable> variables = {}) {
    this->nodes = nodes;
    this->lines = lines;
    this->variables = variables;
    this->index = 0;
    this->speed = 2000;
    this->time = 0;
}

void Script::Draw(SDL_Renderer* renderer) {
    for (int i = 0; i < this->lines.size(); i++) {
        this->lines[i].Draw(renderer, this->nodes);
    }

    for (int i = 0; i < this->nodes.size(); i++) {
        this->nodes[i].Draw(renderer, circleImg);
    }
}

bool Script::Run(Compile compile) {
    if (this->index >= this->nodes.size()) {return false;}

    time++;
    if (time < this->speed) {return false;}
    time = 0;

    this->nodes[this->index].isOn = false;
    bool isTrueLine = false;
    for (int i = 0; i < this->lines.size(); i++) {
        if (this->lines[i].start == this->index) {
            if (compile.Check(this->lines[i].command)) {
                this->index = this->lines[i].end;
                isTrueLine = true;
                break;
            }
        }
    }

    if (isTrueLine) {
        compile.Run(this->nodes[this->index].command);
        this->nodes[this->index].isOn = true;
        return true;
    }
    return false;
}
