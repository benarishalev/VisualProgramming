#ifndef PLACEMENT_APP
#define PLACEMENT_APP

#include <SDL3_ttf/SDL_ttf.h>
#include "../buttonClass/button.hpp"
#include "../nodeClass/node.hpp"
#include "../GLOBALS/globals.hpp"
#include "../dialogClass/dialog.hpp"
#include "../textBoxClass/textBox.hpp"

class Script;

class Placement {
    public:
        std::vector<Button> buttons;
        bool buttonsClick[3] = {false, false, false};
        int nodeLineIndex;
        int nodeDialogIndex;
        int lineDialogIndex;
        int moveNodeIndex;
        Dialog nodeDialog;
        Dialog lineDialog;
        bool showNodeDialog;
        bool showLineDialog;
        TextBox codeText;
        bool showCodeText;
        
    Placement(SDL_Renderer* renderer, int WIDTH, int HEIGHT);

    void PlaceNode(Script& script, int x, int y);
    bool canPlaceNode(Script& script, int x, int y);
    void PlaceLine(Script& script, int x, int y);
    int getNearestNodeIndex(Script& script, int x, int y);
    bool Click(int x, int y);
    void Draw(SDL_Renderer* renderer);
    void updatePosition(int WIDTH, int HEIGHT);

    void openNodeDialog(Script& script, int x, int y, SDL_Renderer* renderer);
    void openLineDialog(Script& script, int x, int y, SDL_Renderer* renderer);
    bool ClickNodeDialog(Script& script, int x, int y, SDL_Renderer* renderer);
    bool ClickLineDialog(Script& script, int x, int y, SDL_Renderer* renderer);

    void removeNode(Script& script, int x, int y);
    void removeLine(Script& script, int index);

    void moveNode(Script& script, int x, int y);
    void moveNodeUpdate(Script& script);
    int getClickedNodeIndex(Script& script, int x, int y);
    void getInput(Script& script, char x, SDL_Renderer* renderer);
};

#endif