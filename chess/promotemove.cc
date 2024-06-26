#include "promotemove.h"
#include <iostream>
#include <string>

using namespace std;

// promoteMove::promoteMove(Board *b, Position start, Position end, string colour) : Move{b, start, end, colour} {}

// Board promoteMove::movePiece(string promoteTo)
// {
//     // move should be a valid move already
//     Board update = b;
//     Square starting = update.getSquare(start.x, start.y);
//     Square ending = update.getSquare(end.x, end.y);
//     Piece *promotingTo = nullptr;

//     if (promoteTo == "rook") {
//         promoteTo = new Rook{colour};
//     } else if (promoteTo == "knight") {
//         promoteTo = new Knight{colour};
//     } else if (promoteTo == "bishop") {
//         promoteTo = new Bishop{colour};
//     } else if (promoteTo == "queen") {
//         promoteTo = new Queen{colour};
//     }

//     update.getSquare(start.x, start.y).setPiece(nullptr);
//     if (update.getSquare(end.x, end.y).getPiece())
//     {
//         update.getSquare(end.x, end.y).setPiece(nullptr);
//     }
//     update.getSquare(end.x, end.y).setPiece(promoteTo);
//     promoteTo->sethasMoved();
//     return update;
// }
