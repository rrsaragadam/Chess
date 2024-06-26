#ifndef SQUARE_H
#define SQUARE_H
#include "piece.h"

class Square {
private:
 Position position;
 Piece *piece;
 
public:
 Square(int x, int y, Piece *piece = nullptr);
 Square(Square &other);
 Square &operator=(const Square &other);
//  ~Square();
 void setPiece(Piece *piece);
 Piece* getPiece();
 Position getPosition();
};

#endif
