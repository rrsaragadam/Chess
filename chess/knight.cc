#include "knight.h"
#include <iostream>
using namespace std;

Knight::Knight(std::string colour) : Piece{colour, "knight"} {}

Piece* Knight::clone()
{
    Piece *newB = new Knight{getColour()};
    if (gethasMoved())
    {
        newB->setHasMoved(true);
    }
    return newB;
}

std::vector<Position> Knight::getMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1, m2, m3, m4, m5, m6, m7, m8;
    m1.x = row - 2;
    m1.y = col + 1;
    moves.emplace_back(m1);
    m2.x = row - 2;
    m2.y = col - 1;
    moves.emplace_back(m2);
    m3.x = row - 1;
    m3.y = col - 2;
    moves.emplace_back(m3);
    m4.x = row - 1;
    m4.y = col + 2;
    moves.emplace_back(m4);
    m5.x = row + 1;
    m5.y = col + 2;
    moves.emplace_back(m5);
    m6.x = row + 1;
    m6.y = col - 2;
    moves.emplace_back(m6);
    m7.x = row + 2;
    m7.y = col - 1;
    moves.emplace_back(m7);
    m8.x = row + 2;
    m8.y = col + 1;
    moves.emplace_back(m8);
    moves = remove(moves);
    // for ( auto i : moves) {
    //     cout << "possible move: " << i.x << i.y << endl;
    // }
    return moves;
}

Knight::~Knight() {}
