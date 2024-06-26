#include "king.h"
using namespace std;

King::King(std::string colour) : Piece{colour, "king"} {}

Piece* King::clone()
{
    Piece *newB = new King{getColour()};
    if (gethasMoved())
    {
        newB->setHasMoved(true);
    }
    return newB;
}

std::vector<Position> King::getMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1;
    Position castle;
    Position castle1;
    // if (!gethasMoved()) {
    //     castle.x = row;
    //     castle.y = col+2;
    //     castle1.x = row;
    //     castle1.y = col-2;
    //     moves.emplace_back(castle);
    //     moves.emplace_back(castle1);
    // }
    if (row -1 >= 0) { 
        m1.x = row-1;
        m1.y = col;
        moves.emplace_back(m1);
    }
    if (col - 1 >= 0)
    {
        m1.x = row;
        m1.y = col-1;
        moves.emplace_back(m1);
    }
    if (row + 1 <= 7)
    {
        m1.x = row + 1;
        m1.y = col;
        moves.emplace_back(m1);
    }
    if (col + 1 <= 7)
    {
        m1.x = row;
        m1.y = col+1;
        moves.emplace_back(m1);
    }
    if (row + 1 <= 7 && col + 1 <= 7) {
        m1.x = row + 1;
        m1.y = col + 1;
        moves.emplace_back(m1);
    }
    if (row + 1 <= 7 && col - 1 >= 0)
    {
        m1.x = row + 1;
        m1.y = col - 1;
        moves.emplace_back(m1);
    }
    if (row - 1 >= 0 && col + 1 <= 7)
    {
        m1.x = row - 1;
        m1.y = col + 1;
        moves.emplace_back(m1);
    }
    if (row - 1 >= 0 && col - 1 >= 0)
    {
        m1.x = row - 1;
        m1.y = col - 1;
        moves.emplace_back(m1);
    }

    moves = remove(moves);
    return moves;
}

King::~King() {}

