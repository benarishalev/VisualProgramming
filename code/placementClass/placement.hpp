#ifndef PLACEMENT_APP
#define PLACEMENT_APP

#include <SDL3_ttf/SDL_ttf.h>
#include "../buttonClass/button.hpp"
#include "../scriptClass/script.hpp"
#include "../nodeClass/node.hpp"
#include "../globals.hpp"
#include "../dialogClass/dialog.hpp"

class Placement {
    public:
        Button nodeButton;
        Button lineButton;
        bool nodeClick;
        bool lineClick;
        int nodeLineIndex;
        TTF_Font*& font;
        Dialog dialog;
        bool showDialog;
        int nodeDialogIndex;
        
    Placement(SDL_Renderer* renderer, TTF_Font*& font, int WIDTH, int HEIGHT);

    void PlaceNode(Script& script, int x, int y);
    bool canPlaceNode(Script& script, int x, int y);
    void PlaceLine(Script& script, int x, int y);
    int getNearestNodeIndex(Script& script, int x, int y);
    bool Click(int x, int y);
    void Draw(SDL_Renderer* renderer);
    void updatePosition(int WIDTH, int HEIGHT);
    void openDialog(Script& script, int x, int y);
    bool ClickDialog(Script& script, int x, int y);
    void removeNode(Script& script, int x, int y);
};

#endif