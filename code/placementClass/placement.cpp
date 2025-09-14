#include "placement.hpp"

Placement::Placement(SDL_Renderer* renderer, TTF_Font*& font, int WIDTH, int HEIGHT) : font(font) {
    // set up the buttons
    Button nodeButton = Button({100, (float)HEIGHT-100}, {150, 75});
    nodeButton.setText(renderer, "Node", font);
    Button lineButton = Button({300, (float)HEIGHT-100}, {150, 75});
    lineButton.setText(renderer, "Line", font);
    Button moveButtom = Button({500, (float)HEIGHT-100}, {150, 75});
    moveButtom.setText(renderer, "Move", font);
    this->buttons.push_back(nodeButton);
    this->buttons.push_back(lineButton);
    this->buttons.push_back(moveButtom);

    this->nodeLineIndex = -1;
    this->showDialog = false;
    this->nodeDialogIndex = -1;
    this->moveNodeIndex = -1;
    this->dialog.setButtons(renderer, {"remove", "Code"}, font);
    this->showCodeText = false;
}

void Placement::PlaceNode(Script& script, int x, int y) {
    if (this->buttonsClick[0]) {
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

int Placement::getClickedNodeIndex(Script& script, int x, int y) {
    for (int i = 0; i < script.nodes.size(); i++) {
        if (getDistance(x, y, script.nodes[i].position.x, script.nodes[i].position.y) < script.nodes[i].size / 2 + 10) {
            return i;
        }
    }
    return -1;
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

void Placement::moveNode(Script& script, int x, int y) {
    if (!this->buttonsClick[2]) {
        this->moveNodeIndex = -1;
        SDL_SetCursor(regularCursor);
        return;
    }
    // if not grab then try to grab
    // else remove the grab
    if (this->moveNodeIndex == -1) {
        this->moveNodeIndex = getClickedNodeIndex(script, x, y);
        if (this->moveNodeIndex != -1) {
            SDL_SetCursor(handCursor);
        }
    } else {
        this->moveNodeIndex = -1;
        SDL_SetCursor(regularCursor);
    }
}

void Placement::moveNodeUpdate(Script& script) {
    if (this->moveNodeIndex != -1 && this->buttonsClick[2]) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        script.nodes[this->moveNodeIndex].position.x = x;
        script.nodes[this->moveNodeIndex].position.y = y;
    }
}

void Placement::PlaceLine(Script& script, int x, int y) {
    // if button isnt clicked and there is a node already clicked
    // then try to create a line if its not the same node
    if (!this->buttonsClick[1]) {
        this->nodeLineIndex = -1;
        return;
    }
    if (this->nodeLineIndex == -1) {
        this->nodeLineIndex = getNearestNodeIndex(script, x, y);
        return;
    }
    int index = getNearestNodeIndex(script, x, y);
    if (index == -1) {
        this->nodeLineIndex = -1;
        return;
    }
    if (index != this->nodeLineIndex) {
        Line add = Line({this->nodeLineIndex, index});
        this->nodeLineIndex = -1;
        for (int i = 0; i < script.lines.size(); i++) {
            if (script.lines[i] == add) {
                script.lines.erase(script.lines.begin() + i);
                return;
            }
        }
        script.lines.push_back(add);
    }
}

bool Placement::Click(int x, int y) {
    this->showDialog = false;
    for (int i = 0; i < this->buttons.size(); i++) {
        if (this->buttons[i].isClick(x, y)) {
            for (int j = 0; j < 3; j++) {
                this->buttonsClick[j] = false;
            }
            this->buttonsClick[i] = true;
            return true;
        }
    }
    return false;
}

void Placement::Draw(SDL_Renderer* renderer) {
    for (int i = 0; i < this->buttons.size(); i++) {
        this->buttons[i].Draw(renderer, (this->buttonsClick[i] ? SDL_Color{100, 100, 100} : SDL_Color{0, 0, 0}));
    }
    if (this->showDialog) {
        this->dialog.Draw(renderer);
    }
    if (this->showCodeText && this->showDialog) {
        this->codeText.Draw(renderer, this->dialog.x + 220, this->dialog.y + 50);
    }
}

void Placement::updatePosition(int WIDTH, int HEIGHT) {
    for (int i = 0; i < this->buttons.size(); i++) {
        this->buttons[i].position = {(float)(100 + 200*i), (float)(HEIGHT-100)};
    }
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

bool Placement::ClickDialog(Script& script, int x, int y, SDL_Renderer* renderer, TTF_Font* font) {
    if (this->dialog.getPressed(x, y) == 0) {
        removeNode(script, x, y);
        this->showDialog = false;
        this->nodeDialogIndex = -1;
        return true;
    }
    if (this->dialog.getPressed(x, y) == 1) {
        this->showCodeText = !this->showCodeText;
        this->codeText.text = script.nodes[this->nodeDialogIndex].command;
        this->codeText.setTexture(renderer, font, {255, 255, 255});
        return true;
    }
    return false;
}

void Placement::getInput(Script& script, char x, SDL_Renderer* renderer, TTF_Font* font) {
    if (this->showCodeText) {
        this->codeText.handleInput(x);
        script.nodes[this->nodeDialogIndex].command = this->codeText.text;
        this->codeText.setTexture(renderer, font, {255, 255, 255});
    }
}