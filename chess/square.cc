#include "square.h"
#include <iostream>
using namespace std;

Square::Square(int x, int y, Piece *piece) : piece{piece}
 { 
    Position p{x, y};
    position = p;
 }

Square::Square(Square &other) {
   // cout << "Square copy called" << endl;
   position = other.position;
   if (!other.piece) {
      piece = nullptr;
   } else {
      piece = other.piece->clone();
   }
}

Square &Square::operator=(const Square &other) {
   // cout << "Square operator called" << endl;
   if (this == &other) return *this;

   position = other.position;
   if (!other.piece) {
      piece = nullptr;
   } else {
      piece = other.piece->clone();
   }
   return *this;
}


//  Square::~Square() {
//    delete piece;
//  }

void Square::setPiece(Piece *piece) {
   this->piece = piece;
}

Piece* Square::getPiece() {
   return piece;
}

Position Square::getPosition() {
   return position;
}