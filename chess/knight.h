#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece {
private:
 std::string colour;
 std::string type;

public:
 Knight(std::string colour);
 Piece *clone() override;
 std::vector<Position> getMoves(Position curpos) override;
 ~Knight();
};

#endif
