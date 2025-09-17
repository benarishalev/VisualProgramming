#include "script.hpp"
#include "../placementClass/placement.hpp"

Script::Script(std::vector<Node> nodes, std::vector<Line> lines, std::map<std::string, Variable> variables = {}) {
    this->nodes = nodes;
    this->lines = lines;
    this->variables = variables;
    this->index = 0;
    this->speed = 200;
    this->runCodeCircleSpeed = 200;
    this->time = 0;
    this->runCodePosition = Point(0, 0);
}

void Script::Update() {
    runCodePosition.x += (this->nodes[this->index].position.x - runCodePosition.x) / this->runCodeCircleSpeed;
    runCodePosition.y += (this->nodes[this->index].position.y - runCodePosition.y) / this->runCodeCircleSpeed;
}
void Script::drawRunCirlce(SDL_Renderer* renderer, SDL_Texture* circleImg) {
    SDL_SetTextureColorMod(circleImg, 255, 0, 0);
    SDL_FRect rect;
    rect.w = 25;
    rect.h = 25;
    rect.x = runCodePosition.x - rect.w/2;
    rect.y = runCodePosition.y - rect.h/2;
    SDL_RenderTexture(renderer, circleImg, NULL, &rect);
    SDL_SetTextureColorMod(circleImg, 255, 255, 255);
}

void Script::Draw(SDL_Renderer* renderer, SDL_Texture* circleImg, Placement placement, bool runningCode) {
    for (int i = 0; i < this->lines.size(); i++) {
        this->lines[i].Draw(renderer, this->nodes);
    }

    for (int i = 0; i < this->nodes.size(); i++) {
        if (i == placement.nodeLineIndex) {
            SDL_SetTextureColorMod(circleImg, 255, 255, 0);
        } else {
            SDL_SetTextureColorMod(circleImg, 255, 255, 255);
        }
        this->nodes[i].Draw(renderer, circleImg);
    }

    if (runningCode) {
        this->drawRunCirlce(renderer, circleImg);
    }
}

std::string Script::Run(Compile compile) {
    if (this->index >= this->nodes.size()) {
        return "End Of Program";
    }

    time++;
    if (time < this->speed) {return "";}
    time = 0;

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
        std::string codeError = compile.Run(this->nodes[this->index].command);
        return codeError;
    }
    return "End Of Program";
}
