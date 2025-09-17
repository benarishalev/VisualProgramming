#include "placement.hpp"
#include "../scriptClass/script.hpp"

Placement::Placement(SDL_Renderer* renderer, int WIDTH, int HEIGHT) {
    // set up the buttons
    Button nodeButton = Button({100, (float)HEIGHT-100}, {150, 75});
    nodeButton.setText(renderer, "Node", pixelFont);
    Button lineButton = Button({300, (float)HEIGHT-100}, {150, 75});
    lineButton.setText(renderer, "Line", pixelFont);
    Button moveButtom = Button({500, (float)HEIGHT-100}, {150, 75});
    moveButtom.setText(renderer, "Move", pixelFont);
    this->buttons.push_back(nodeButton);
    this->buttons.push_back(lineButton);
    this->buttons.push_back(moveButtom);

    this->nodeLineIndex = -1;
    this->moveNodeIndex = -1;

    this->showNodeDialog = false;
    this->showLineDialog = false;
    this->nodeDialogIndex = -1;
    this->lineDialogIndex = -1;

    this->nodeDialog.setButtons(renderer, {"remove", "code"}, pixelFont);
    this->lineDialog.setButtons(renderer, {"remove", "code"}, pixelFont);
    this->showCodeText = false;
}

void Placement::PlaceNode(Script& script, int x, int y) {
    if (this->buttonsClick[0]) {
        if (canPlaceNode(script, x, y)) {
            script.nodes.push_back(Node(Point(x, y)));
        }
    }
}

void Placement::removeLine(Script& script, int index) {
    if (this->lineDialogIndex == -1) {
        return;
    }
    script.lines.erase(script.lines.begin() + this->lineDialogIndex);
}

void Placement::removeNode(Script& script, int x, int y) {
    // if removing node then make sure
    // that you are not connecting line
    // to the removed node :)
    this->nodeLineIndex = -1;
    if (this->nodeDialogIndex == -1) {
        std::cout << "No node selected" << std::endl;
        return;
    }
    for (int j = 0; j < script.lines.size(); j++) {
        if (script.lines[j].start == nodeDialogIndex || script.lines[j].end == nodeDialogIndex) {
            script.lines.erase(script.lines.begin() + j);
            j--;
        }
    }
    for (int i = 0; i < script.lines.size(); i++) {
        if (script.lines[i].start > nodeDialogIndex) script.lines[i].start--;
        if (script.lines[i].end > nodeDialogIndex) script.lines[i].end--;
    }
    if (nodeDialogIndex < script.nodes.size()) {
        script.nodes.erase(script.nodes.begin() + nodeDialogIndex);
        nodeDialogIndex = -1;
    }
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
        script.nodes[this->moveNodeIndex].position.x += (x - script.nodes[this->moveNodeIndex].position.x) / 100;
        script.nodes[this->moveNodeIndex].position.y += (y - script.nodes[this->moveNodeIndex].position.y) / 100;
    }
}

void Placement::PlaceLine(Script& script, int x, int y) {
    // if button isnt clicked and there is a node already clicked
    // then try to create a line
    // if its the same node then remove the selection
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
    if (index == this->nodeLineIndex) {
        this->nodeLineIndex = -1;
        return;
    }
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

bool Placement::Click(int x, int y) {
    this->showNodeDialog = false;
    this->showLineDialog = false;
    this->showCodeText = false;
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
    if (this->showNodeDialog) {
        this->nodeDialog.Draw(renderer);
    }
    if (this->showLineDialog) {
        this->lineDialog.Draw(renderer);
    }
    if (this->showCodeText) {
        if (this->showNodeDialog) {
            this->codeText.Draw(renderer, this->nodeDialog.x + 220, this->nodeDialog.y + 50);
        } else if (this->showLineDialog) {
            this->codeText.Draw(renderer, this->lineDialog.x + 220, this->lineDialog.y + 50);
        }
    }
}

void Placement::updatePosition(int WIDTH, int HEIGHT) {
    for (int i = 0; i < this->buttons.size(); i++) {
        this->buttons[i].position = {(float)(100 + 200*i), (float)(HEIGHT-100)};
    }
}

void Placement::openNodeDialog(Script& script, int x, int y, SDL_Renderer* renderer) {
    this->showNodeDialog = false;
    if (!this->buttonsClick[0]) {
        return;
    }
    for (int i = 0; i < script.nodes.size(); i++) {
        if (getDistance(x, y, script.nodes[i].position.x, script.nodes[i].position.y) < script.nodes[i].size / 2 + 10) {
            this->showNodeDialog = true;
            this->codeText.text = script.nodes[i].command;
            this->codeText.setTexture(renderer, codeFont, {255, 255, 255});
            this->nodeDialogIndex = i;
            this->nodeDialog.x = script.nodes[i].position.x;
            this->nodeDialog.y = script.nodes[i].position.y;
            return;
        }
    }
}

void Placement::openLineDialog(Script& script, int x, int y, SDL_Renderer* renderer) {
    this->showLineDialog = false;
    if (!this->buttonsClick[1]) {
        return;
    }
    for (int i = 0; i < script.lines.size(); i++) {
        // getting the middle of the line
        int xMiddleLine = (script.nodes[script.lines[i].start].position.x + script.nodes[script.lines[i].end].position.x) / 2;
        int yMiddleLine = (script.nodes[script.lines[i].start].position.y + script.nodes[script.lines[i].end].position.y) / 2;
        if (getDistance(x, y, xMiddleLine, yMiddleLine) < 100) {
            this->showLineDialog = true;
            this->codeText.text = script.lines[i].command;
            this->codeText.setTexture(renderer, codeFont, {255, 255, 255});
            this->lineDialogIndex = i;
            this->lineDialog.x = xMiddleLine;
            this->lineDialog.y = yMiddleLine;
            return;
        }
    }
}

bool Placement::ClickNodeDialog(Script& script, int x, int y, SDL_Renderer* renderer) {
    if (this->nodeDialog.getPressed(x, y) == 0 && script.nodes.size() > 1) {
        removeNode(script, x, y);
        this->showNodeDialog = false;
        this->showCodeText = false;
        this->nodeDialogIndex = -1;
        return true;
    }
    // makes sure that when i tried to change the code
    // it wont crash
    if (this->nodeDialog.getPressed(x, y) == 1 && this->showNodeDialog && this->nodeDialogIndex != -1) {
        this->showCodeText = !this->showCodeText;
        this->codeText.text = script.nodes[this->nodeDialogIndex].command;
        this->codeText.setTexture(renderer, codeFont, {255, 255, 255});
        return true;
    }
    return false;
}

bool Placement::ClickLineDialog(Script& script, int x, int y, SDL_Renderer* renderer) {
    if (this->lineDialog.getPressed(x, y) == 0) {
        removeLine(script, this->lineDialogIndex);
        this->showLineDialog = false;
        this->showCodeText = false;
        this->lineDialogIndex = -1;
        return true;
    }
    // makes sure that when i tried to change the code
    // it wont crash
    if (this->lineDialog.getPressed(x, y) == 1 && this->showLineDialog && this->lineDialogIndex != -1) {
        this->showCodeText = !this->showCodeText;
        this->codeText.text = script.lines[this->lineDialogIndex].command;
        this->codeText.setTexture(renderer, codeFont, {255, 255, 255});
        return true;
    }
    return false;
}

void Placement::getInput(Script& script, char x, SDL_Renderer* renderer) {
    if (this->showCodeText) {
        this->codeText.handleInput(x);
        if (this->showLineDialog) {
            script.lines[this->lineDialogIndex].command = this->codeText.text;
        } else if (this->showNodeDialog) {
            script.nodes[this->nodeDialogIndex].command = this->codeText.text;
        }
        this->codeText.setTexture(renderer, codeFont, {255, 255, 255});
    }
}