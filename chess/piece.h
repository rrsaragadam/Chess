#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <utility>
#include <vector>
#include "player.h"

struct Position
{
    int x;
    int y;
    Position(int x = 0, int y = 0) : x{x}, y{y} {}
};

class Piece {
private:
 std::string colour;
 std::string type;
 bool hasMoved = false;
 Position curpos;

 protected:
 std::vector<Position> remove(std::vector <Position> n);

public:
 Piece(std::string colour, std::string type);
 virtual std::vector<Position> getMoves(Position curpos) = 0;
 virtual Piece *clone() = 0;
 std::string getColour();
 std::string getType();
 bool gethasMoved();
 void setHasMoved(bool state);
 virtual ~Piece();
};

#endif
