#include "queen.h"
#include <iostream>
using namespace std;

Queen::Queen(std::string colour) : Piece{colour, "queen"} {}

Piece* Queen::clone()
{
    Piece *newB = new Queen{getColour()};
    if (gethasMoved())
    {
        newB->setHasMoved(true);
    }
    return newB;
}

std::vector<Position> Queen::getMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1, m2, m3, m4, m5, m6, m7, m8;
    for (int i = 1; i <= 7; ++i) {
        m1.x = row+ i; // **lines**
        m1.y = col; 
        m2.x = row; 
        m2.y = col + i; 
        m3.x = row;
        m3.y = col - i;
        m4.x = row - i;
        m4.y = col;
        m5.x = row + i; // **Diagonals**
        m5.y = col + i;
        m6.x = row - i;
        m6.y = col - i;
        m7.x = row + i;
        m7.y = col - i;
        m8.x = row - i;
        m8.y = col + i;
        moves.emplace_back(m1);
        moves.emplace_back(m2);
        moves.emplace_back(m3);
        moves.emplace_back(m4);
        moves.emplace_back(m5);
        moves.emplace_back(m6);
        moves.emplace_back(m7);
        moves.emplace_back(m8);
    }
    moves = remove(moves);
    // cout << "LEN CHECK: " << moves.size() << endl;
    // for ( auto i : moves) {
    //     cout << "possible move: " << i.x << i.y << endl;
    // }
    return moves;
}

    Queen::~Queen() {}
