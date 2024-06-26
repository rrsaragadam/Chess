#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
private:
 std::string colour;
 std::string type;

public:
 Pawn(std::string colour);
 std::vector<Position> getMoves(Position curpos) override;
 std::vector<Position> getCaptureMoves(Position curpos);
 Piece *clone() override;
 ~Pawn();
};

#endif
