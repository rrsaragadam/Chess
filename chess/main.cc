#include "game.h"
#include "display.h"
#include <iostream>

using namespace std;
int main () {
    Display *d = new Display{};
    Game *theGame = new Game{d};
    theGame->play();
}
