#include "placement.hpp"

Placement::Placement(SDL_Renderer* renderer, TTF_Font*& font, int WIDTH, int HEIGHT) : font(font) {
    this->nodeButton = Button({100, (float)HEIGHT-100}, {150, 75});
    this->nodeButton.setText(renderer, "Node", font);
    this->lineButton = Button({300, (float)HEIGHT-100}, {150, 75});
    this->lineButton.setText(renderer, "Line", font);
    this->nodeClick = false;
    this->lineClick = false;
    this->nodeLineIndex = -1;
    this->showDialog = false;
    this->nodeDialogIndex = -1;
    this->dialog.setButtons(renderer, {"remove"}, font);
}

void Placement::PlaceNode(Script& script, int x, int y) {
    if (this->nodeClick) {
        if (canPlaceNode(script, x, y)) {
            script.nodes.push_back(Node(Point(x, y)));
        }
    }
}

void Placement::removeNode(Script& script, int x, int y) {
    for (int j = 0; j < script.lines.size(); j++) {
        if (script.lines[j].start == nodeDialogIndex || script.lines[j].end == nodeDialogIndex) {
            script.lines.erase(script.lines.begin() + j);
            j--;
        }
    }
    script.nodes.erase(script.nodes.begin() + nodeDialogIndex);
}

bool Placement::canPlaceNode(Script& script, int x, int y) {
    for (int i = 0; i < script.nodes.size(); i++) {
        if (getDistance(x, y, script.nodes[i].position.x, script.nodes[i].position.y) < script.nodes[i].size / 2 + 10) {
            return false;
        }
    }
    return true;
}

int Placement::getNearestNodeIndex(Script& script, int x, int y) {
    int minIndex = -1;
    double minDistance = 1000000000;
    for (int i = 0; i < script.nodes.size(); i++) {
        double distance = getDistance(x, y, script.nodes[i].position.x, script.nodes[i].position.y);
        if (distance < minDistance) {
            minDistance = distance;
            minIndex = i;
        }
    }
    return minIndex;
}

void Placement::PlaceLine(Script& script, int x, int y) {
    if (this->lineClick) {
        if (this->nodeLineIndex != -1) {
            int index = getNearestNodeIndex(script, x, y);
            if (index != -1 && index != this->nodeLineIndex) {
                Line add = Line({this->nodeLineIndex, index});
                this->nodeLineIndex = -1;
                for (int i = 0; i < script.lines.size(); i++) {
                    if (script.lines[i] == add) {
                        script.lines.erase(script.lines.begin() + i);
                        return;
                    }
                }
                script.lines.push_back(add);
            } else if (index == -1) {
                this->nodeLineIndex = -1;
            }
        } else {
            this->nodeLineIndex = getNearestNodeIndex(script, x, y);
        }
    } else {
        this->nodeLineIndex = -1;
    }
}

bool Placement::Click(int x, int y) {
    if (this->nodeButton.isClick(x, y)) {
        this->nodeClick = !this->nodeClick;
        this->lineClick = false;
        return true;
    } else if (this->lineButton.isClick(x, y)) {
        this->lineClick = !this->lineClick;
        this->nodeClick = false;
        return true;
    }
    return false;
}

void Placement::Draw(SDL_Renderer* renderer) {
    this->nodeButton.Draw(renderer, (this->nodeClick ? SDL_Color{100, 100, 100} : SDL_Color{0, 0, 0}));
    this->lineButton.Draw(renderer, (this->lineClick ? SDL_Color{100, 100, 100} : SDL_Color{0, 0, 0}));
    if (this->showDialog) {
        this->dialog.Draw(renderer);
    }
}

void Placement::updatePosition(int WIDTH, int HEIGHT) {
    this->nodeButton.position = {100, (float)HEIGHT-100};
    this->lineButton.position = {300, (float)HEIGHT-100};
}

void Placement::openDialog(Script& script, int x, int y) {
    this->showDialog = false;
    for (int i = 0; i < script.nodes.size(); i++) {
        if (getDistance(x, y, script.nodes[i].position.x, script.nodes[i].position.y) < script.nodes[i].size / 2 + 10) {
            this->showDialog = true;
            this->nodeDialogIndex = i;
            this->dialog.x = script.nodes[i].position.x;
            this->dialog.y = script.nodes[i].position.y;
            return;
        }
    }
}

bool Placement::ClickDialog(Script& script, int x, int y) {
    if (this->dialog.getPressed(x, y) == 0) {
        removeNode(script, x, y);
        this->showDialog = false;
        this->nodeDialogIndex = -1;
        return true;
    }
    return false;
}