#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
private:
 std::string colour;
 std::string type;

public:
 Bishop(std::string colour);
 std::vector<Position> getMoves(Position curpos) override;
 Piece *clone() override;
 ~Bishop();
};

#endif
