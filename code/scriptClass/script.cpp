#include "script.hpp"

Script::Script(std::vector<Node> nodes, std::vector<Line> lines, std::map<std::string, Variable> variables = {}) {
    this->nodes = nodes;
    this->lines = lines;
    this->variables = variables;
    this->index = 0;
    this->speed = 100;
    this->time = 0;
}

void Script::Draw(SDL_Renderer* renderer, SDL_Texture* circleImg) {
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
    bool found = false;
    for (int i = 0; i < this->lines.size(); i++) {
        if (this->lines[i].start == this->index) {
            this->index = this->lines[i].end;
            found = true;
            break;
        }
    }

    if (found) {
        //std::cout << this->nodes[this->index].command << std::endl;
        compile.Run(this->nodes[this->index].command);
        this->nodes[this->index].isOn = true;
        return true;
    }
    return false;
}
