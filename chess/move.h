#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "board.h"
#include "square.h"
#include "piece.h"

class Move {
protected:
    Board *board;
    Position start;
    Position end;
    std::string colour;

public:
    Move(Board* b, Position start, Position end, std::string colour);
    bool isValid();
    bool isValidPath();
    std::string getMoveType();
    bool isEnpassant();
    bool isPromotepawn();
    bool isCastle();
    bool isNormalKill();
    bool isKingSafe();
    void normalMove();
    void killMove();
    void promoteMove(std::string promoteTo);
    bool castleMove();
    void enpassantMove();
};

#endif