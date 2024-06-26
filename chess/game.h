#ifndef GAME_H
#define GAME_H

#include "display.h"
#include "board.h"
#include "player.h"
class Game {
private:
 Display *display;
 Board *board;
 Player *player1 = nullptr;
 Player *player2 = nullptr;
 int turn = 1;
 //int p1score = 0;
 //int p2score = 0;

public:
 Game(Display *d);
 void play();
 void initGame();
 void setup();
 void addPiece(char piece, std::string square);
 void removePiece(std::string square);
 void move(std::string startPos, std::string endPos, std::string upgrade);
 bool isValidPos(std::string square);
 ~Game(); 
};

#endif
