#include "rook.h"
#include "iostream"
using namespace std;

Rook::Rook(std::string colour) : Piece{colour, "rook"} {}

Piece* Rook::clone() {
    Piece *newB = new Rook{getColour()};
    if (gethasMoved())
    {
        newB->setHasMoved(true);
    }
    return newB;
}

std::vector<Position> Rook::getMoves(Position curpos) {
    vector<Position> moves;
    int row = curpos.x;
    int col = curpos.y;
    Position m1;
    for (int i = row+1; i < 8; ++i) {
        m1.x = i;
        m1.y = col;
        moves.emplace_back(m1);
    }
    for (int i = row-1; i >= 0; --i) {
        m1.x = i;
        m1.y = col;
        moves.emplace_back(m1);
    }
    for (int i = col+1; i < 8; ++i)
    {
        m1.x = row;
        m1.y = i;
        moves.emplace_back(m1);
    }
    for (int i = col-1; i >= 0; --i)
    {
        m1.x = row;
        m1.y = i;
        moves.emplace_back(m1);
    }
    moves = remove(moves);
    // cout << "LEN CHECK: " << moves.size() << endl;
    // for (auto i : moves) {
    //     cout << "possible move: " << i.x << i.y << endl;
    // }
    return moves;
} 

    Rook::~Rook() {}
