#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "square.h"
#include "board.h"
#include "move.h"
class Computer : public Player {
public:
    int level;
public:
    Computer(int level, std::string colour, std::string name);
    int getLevel();
    std::pair<Position, Position> getMove(Board *b);
    std::pair<Position, Position> getLevel1Move(Board *b);
    std::pair<Position, Position> getLevel2Move(Board *b);
};

#endif
