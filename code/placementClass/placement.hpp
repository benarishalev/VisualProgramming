#ifndef PLACEMENT_APP
#define PLACEMENT_APP

#include <SDL3_ttf/SDL_ttf.h>
#include "../buttonClass/button.hpp"
#include "../scriptClass/script.hpp"
#include "../nodeClass/node.hpp"
#include "../GLOBALS/globals.hpp"
#include "../dialogClass/dialog.hpp"
#include "../textBoxClass/textBox.hpp"

class Placement {
    public:
        std::vector<Button> buttons;
        bool buttonsClick[3] = {false, false, false};
        int nodeLineIndex;
        int nodeDialogIndex;
        int moveNodeIndex;
        TTF_Font*& font;
        Dialog dialog;
        bool showDialog;
        TextBox codeText;
        bool showCodeText;
        
    Placement(SDL_Renderer* renderer, TTF_Font*& font, int WIDTH, int HEIGHT);

    void PlaceNode(Script& script, int x, int y);
    bool canPlaceNode(Script& script, int x, int y);
    void PlaceLine(Script& script, int x, int y);
    int getNearestNodeIndex(Script& script, int x, int y);
    bool Click(int x, int y);
    void Draw(SDL_Renderer* renderer);
    void updatePosition(int WIDTH, int HEIGHT);
    void openDialog(Script& script, int x, int y, SDL_Renderer* renderer);
    bool ClickDialog(Script& script, int x, int y, SDL_Renderer* renderer, TTF_Font* font);
    void removeNode(Script& script, int x, int y);
    void moveNode(Script& script, int x, int y);
    void moveNodeUpdate(Script& script);
    int getClickedNodeIndex(Script& script, int x, int y);
    void getInput(Script& script, char x, SDL_Renderer* renderer, TTF_Font* font);
};

#endif