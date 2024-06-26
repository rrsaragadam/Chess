#include "killmove.h"
#include <iostream>
#include <string>

using namespace std;

//killMove::killMove(Board *b, Position start, Position end, string colour) : Move{b, start, end, colour} {}

// Board killMove::movePiece(string promoteTo)
// {
//     // move should be a valid move already
//     Board update = b;
//     Square starting = update.getSquare(start.x, start.y);
//     Square ending = update.getSquare(end.x, end.y);
//     Piece *moving = starting.getPiece()->clone();

//     update.getSquare(start.x, start.y).setPiece(nullptr);
//     if (update.getSquare(end.x, end.y).getPiece()) {
//         update.getSquare(end.x, end.y).setPiece(nullptr);
//     }
//     update.getSquare(end.x, end.y).setPiece(moving);
//     return update;
// }
