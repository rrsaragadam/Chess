#ifndef KILLMOVE_H
#define KILLMOVE_H

#include <string>
#include "move.h"
#include "piece.h"
#include "board.h"

class killMove : public Move {
public:
    // killMove(Board *b, Position start, Position end, std::string colour);
    // Board movePiece(std::string promoteTo = 0) override;
};

#endif
