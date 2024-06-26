#include "pawn.h"
#include <iostream>
using namespace std;

Pawn::Pawn(std::string colour) : Piece{colour, "pawn"} {}

Piece* Pawn::clone() {
    Piece *newB = new Pawn{getColour()};
    if (gethasMoved())
    {
        newB->setHasMoved(true);
    }
    return newB;
}

std::vector<Position> Pawn::getCaptureMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1, m2;

    if (getColour() == "black") {
       if (row != 7) {
           m1.x = row + 1;
           m1.y = col + 1;
           m2.x = row + 1;
           m2.y = col - 1;
           moves.emplace_back(m1);
           moves.emplace_back(m2);
       }
    } else {
        if (row != 0) {
            m1.x = row - 1;
            m1.y = col + 1;
            m2.x = row - 1;
            m2.y = col - 1;
            moves.emplace_back(m1);
            moves.emplace_back(m2);
        }
    }
    moves = remove(moves);
    // for ( auto i : moves) {
    //     cout << "possible move: " << i.x << i.y << endl;
    // }
    return moves;
}

std::vector<Position> Pawn::getMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1, m2;
    if (getColour() == "black") {
        m1.x = row+1;
        m1.y = col;
        moves.emplace_back(m1);
        if (gethasMoved() == false) {
            m2.x = row+2;
            m2.y = col;
            moves.emplace_back(m2);
        }
    } else if (getColour() == "white") {
        m1.x = row - 1;
        m1.y = col;
        moves.emplace_back(m1);
        if (gethasMoved() == false)
        {
            m2.x = row - 2;
            m2.y = col;
            moves.emplace_back(m2);
        }
    }
    moves = remove(moves);
    return moves;
}

    Pawn::~Pawn() {}
