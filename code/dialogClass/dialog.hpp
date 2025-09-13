#ifndef DIALOG_APP
#define DIALOG_APP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>
#include "../buttonClass/button.hpp"

class Dialog {
    public:
        std::vector<Button> buttons;
        int x;
        int y;
    
    Dialog();
    void setButtons(SDL_Renderer* renderer, std::vector<std::string> texts, TTF_Font*& font);
    void Draw(SDL_Renderer* renderer);
    int getPressed(int x, int y);
};

#endif