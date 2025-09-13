#include "dialog.hpp"

Dialog::Dialog() : x(0), y(0) {}

void Dialog::setButtons(SDL_Renderer* renderer, std::vector<std::string> texts, TTF_Font*& font) {
    for (int i = 0; i < texts.size(); i++) {
        Button button;
        button.setText(renderer, texts[i], font);
        button.size = {150, 50};
        buttons.push_back(button);
    }
}

void Dialog::Draw(SDL_Renderer* renderer) {
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].position.x = x + 50;
        buttons[i].position.y = y + i*50;
        buttons[i].Draw(renderer, SDL_Color{0, 0, 0});
    }
}

int Dialog::getPressed(int x, int y) {
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].isClick(x, y)) {
            return i;
        }
    }
    return -1;
}