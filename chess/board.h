#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <utility>

#include "square.h"
#include "piece.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

class Board {
public:
 std::vector<std::vector<Square*>> board; // make the board of all 64 squares
 Position recentPawnPos; //to check enpassant

public:
 Board(std::string type);
 Board(const Board &other);
 Board &operator=(const Board &other);
 ~Board();
 Square& getSquare(int x, int y);
 Square* getSquarePoint(int x, int y);
 int isValid();
 Position getRecentPawnPos();
 void setRecentPawnPos(Position p);
 bool isCheck(std::string colour);
 bool isCheckmate(std::string colour);
 bool isStalemate(std::string colour);
 bool isMovePossible(std::string colour);
 std::vector<std::pair<Position, Position>> getMovesPossible(std::string colour);
 std::string getState();
};

#endif
