#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
private:
 std::string colour;
 std::string type;

public:
 Rook(std::string colour);
 std::vector<Position> getMoves(Position curpos) override;
 Piece *clone() override;
 ~Rook();
};

#endif
