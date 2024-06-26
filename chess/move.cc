#include "move.h"
#include <iostream>
#include <vector>
using namespace std;

Move::Move(Board* b, Position start, Position end, std::string colour) : board{b}, start{start}, end{end}, colour{colour} {}

bool Move::isValid() {
    Piece *curPiece = board->getSquare(start.x, start.y).getPiece();
    Piece *pieceToKill = board->getSquare(end.x, end.y).getPiece();

    if (start.x == end.x && start.y == end.y) { //start and end are the same
        return false;//passes
    }
    if (!curPiece) { //start pos piece does not exists
        return false; //passes
    }
    //cout << curPiece->getColour() << " =/= " << colour << endl;
    if (curPiece->getColour() != colour) { //start pos piece does not belongs to them
        return false;
    }
    if (isCastle()) {
        return true;
    }
    if (isEnpassant()) {
        return true;
    }
    //cout << "Status of enpassant:" << isEnpassant() << endl;
    if (isValidPath()) {
         //cout << "MADE IT" << endl;
        vector <Position> validMoves = curPiece->getMoves(start);
        int len = validMoves.size();
        if (!pieceToKill) {    //no piece to kill, just move to square
         //cout << "MADE IT2" << endl;
            for (int i = 0; i < len; i++) {
                if (validMoves[i].x == end.x && validMoves[i].y == end.y) {
                    // cout << "SECOND TIME" << validMoves[i].x << validMoves[i].y << endl;
                    return true;
                }
            }
            return false;
        }
        else {      //piece to kill
            if (curPiece->getType() == "pawn") { //pawn has different capture moves
            //cout << "goes into pawn" << endl;
                Pawn *pawn = dynamic_cast<Pawn *>(curPiece);
                validMoves = pawn->getCaptureMoves(start);
            }
            if (pieceToKill->getColour() == colour) {   //kill same colour
                return false;   
            } else {
                for (int i = 0; i < len; i++) {
                    if (validMoves[i].x == end.x && validMoves[i].y == end.y) {
                        return true;
                    }
                }
                return false;
            }
        }
    } else {
        return false; //not valid path
    }
}

bool Move::isKingSafe() {
    bool safe = false;
    if (isValid()) { 
    // Board *cloneBoard = new Board{"setup"};
    Board cloneBoard = *board;

    Square *startSquare = cloneBoard.getSquarePoint(start.x, start.y); //CLONED BOARD
    Square *endSquare = cloneBoard.getSquarePoint(end.x, end.y);
    Piece *movingPiece = startSquare->getPiece();

    if (endSquare->getPiece()) {
        endSquare->setPiece(nullptr);
    }
    endSquare->setPiece(movingPiece);
    startSquare->setPiece(nullptr);
    // cout << "CLONED BOARD:" << endl;
    // for (int i = 0; i < 8; i++) { //look for other opponent pieces
	// 	for (int j = 0; j < 8; j++) {
    //         Piece *p  = cloneBoard.getSquare(i,j).getPiece();
    //         if (p) {
    //             cout << "x";
    //         } else {
    //             cout << "-";
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << endl;

        if (colour == "white" && cloneBoard.isCheck("white")) {
            // cout << "KING UNSAFE" << endl;
            safe = false;
        }
        else if (colour == "black" && cloneBoard.isCheck("black")) {
            // cout << "KING UNSAFE" << endl;
            safe = false;
        } else {
            safe = true;
        }
    }
    return safe;
}

bool Move::isValidPath() {
    Piece *p = board->getSquare(start.x, start.y).getPiece();
    //cout << "Entering Here!!!!!" << endl;
    if (p->getType() == "knight") { //knight can jump over
        return true;
    }
    if (start.x > end.x && start.y == end.y) { //path N
        for (int i = start.x - 1; i > end.x; i--) {
            Square s = board->getSquare(i, start.y);
            if (s.getPiece()) {
                return false;
            }
        }
        return true;
    }
    else if (start.y < end.y && start.x == end.x) { //path E
        //cout << "Entering Here!!!!!" << endl;
        for (int i = start.y + 1; i < end.y; i++) {
            Square s = board->getSquare(start.x, i);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.x < end.x && start.y == end.y) { //path S
        for (int i = start.x + 1; i < end.x; i++) {
            Square s = board->getSquare(i, start.y);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.y > end.y && start.x == end.x) { //path W
        for (int i = start.y - 1; i > end.y; i--) {
            Square s = board->getSquare(start.x, i);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.x > end.x && start.y > end.y) { //path NE
        for (int i = start.x - 1, j = start.y - 1; i > end.x && j > end.y; i--, j--) {
            Square s = board->getSquare(i, j);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.x < end.x && start.y < end.y) { //path SE
        for (int i = start.x + 1, j = start.y + 1; i < end.x && j < end.y; i++, j++) {
            Square s = board->getSquare(i, j);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.x < end.x && start.y > end.y) { //path SW
        for (int i = start.x + 1, j = start.y - 1; i < end.x && j > end.y; i++, j--) {
            Square s = board->getSquare(i, j);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    else if (start.x > end.x && start.y < end.y) { //path NW
        for (int i = start.x - 1, j = start.y + 1; i > end.x && j < end.y; i--, j++) {
            Square s = board->getSquare(i, j);
            if (s.getPiece()) {
                return false;
            }
        }
    }
    return true;
}

string Move::getMoveType() {
    if (isValid()) {
        //cout << "is a valid move" << endl;
        if (isEnpassant())
            return "enpassant";
        else if (isPromotepawn())
            return "promotepawn";
        else if (isCastle())
            return "castle";
        else if (isNormalKill())
            return "normalkill";
        else
            return "normalmove";
    } else {
        return "Invalid move";
    }
}

bool Move::isEnpassant() {
    Position pawnPos = board->getRecentPawnPos();
    if (pawnPos.x == -1 && pawnPos.y == -1) { //pawn did not move on prev turn
    //cout << "does it fail here" << endl;
        return false;
    }
    Piece *curPiece = board->getSquare(start.x, start.y).getPiece();
    if (curPiece->getType() != "pawn") { //curPiece not a pawn
        return false;
    }
    Square endSquare = board->getSquare(end.x, end.y);
    if (endSquare.getPiece() != nullptr) { //end square occupied
        return false;
    }
    Piece *pawnToKill; 
    if (colour == "white") {
        pawnToKill = board->getSquare(end.x+1, end.y).getPiece(); 
        if (!(pawnPos.x == end.x+1 && pawnPos.y == end.y)) { //not killing the correct pawn that just moved
            return false;
        }
        //cout << "does it enter here" << endl;
        if (pawnPos.x != 3) {
            return false;
        }
    } else {
        pawnToKill = board->getSquare(end.x-1, end.y).getPiece();
        if (!(pawnPos.x == end.x-1 && pawnPos.y == end.y)) { //not killing the correct pawn that just moved
            return false;
        }
        if (pawnPos.x != 4) {
            return false;
        }
    }
    if (pawnToKill && pawnToKill->getType() == "pawn") {
        return true;
    }
    return false;
}



bool Move::isPromotepawn() {
    Piece *curPiece = board->getSquare(start.x, start.y).getPiece();
    if (curPiece && curPiece->getType() == "pawn") {
        if (curPiece->getColour() == "white" && end.x == 0) {
            return true;
        }
        else if (curPiece->getColour() == "black" && end.x == 7) {
            return true;
        }
    }
    return false;
}

bool Move::isCastle() { //king moves two squares towards rook
    Piece *curPiece = board->getSquare(start.x, start.y).getPiece();
    if (curPiece && curPiece->getType() == "king" && !curPiece->gethasMoved() && isValidPath()) {
        Piece *rook;
        if (start.y + 2 == end.y) { //king side castle
            if (curPiece->getColour() == "white") {
                rook = board->getSquare(7,7).getPiece();

            } else {
                rook = board->getSquare(0,7).getPiece();
            }
        } else {
            if (curPiece->getColour() == "white") {
                rook = board->getSquare(7,0).getPiece();
                if (board->getSquare(7, 1).getPiece() != nullptr) { //queen side castle check clear path
                    return false;
                }
            } else {
                rook = board->getSquare(0,0).getPiece();
                if (board->getSquare(0, 1).getPiece() != nullptr) { //queen side castle check clear path
                    return false;
                }
            }
        }
        if (rook && rook->getType() == "rook" && !rook->gethasMoved()) {
            return true;
        }
    }
    return false;
}

bool Move::isNormalKill() {
    Piece *pieceToKill = board->getSquare(end.x, end.y).getPiece();
    if (pieceToKill && pieceToKill->getColour() != colour) {
        return true;
    }
    return false;
}

void Move::normalMove() {
    // cout << "entering normal move" << endl;
    Square starting = board->getSquare(start.x, start.y);
    // Square ending = board->getSquare(end.x, end.y);
    Piece *moving = starting.getPiece();
    board->getSquare(start.x, start.y).setPiece(nullptr);
    board->getSquare(end.x, end.y).setPiece(moving);
    if (moving->getType() == "pawn") {
        moving->setHasMoved(true);
        board->setRecentPawnPos(board->getSquare(end.x, end.y).getPosition());
    }
}

void Move::killMove() {
    //cout << "entering killing move" << endl;
    Square starting = board->getSquare(start.x, start.y);
    Piece *moving = starting.getPiece()->clone();

    board->getSquare(start.x, start.y).setPiece(nullptr);
    if (board->getSquare(end.x, end.y).getPiece())
    {
        board->getSquare(end.x, end.y).setPiece(nullptr);
    }
    board->getSquare(end.x, end.y).setPiece(moving);
}

void Move::promoteMove(string promoteTo) {
    //cout << "entering promote move" << endl;
    Piece *promotingTo = nullptr;

    if (promoteTo == "rook")
    {
        promotingTo = new Rook{colour};
    }
    else if (promoteTo == "knight")
    {
        promotingTo = new Knight{colour};
    }
    else if (promoteTo == "bishop")
    {
        promotingTo = new Bishop{colour};
    }
    else if (promoteTo == "queen")
    {
        promotingTo = new Queen{colour};
    }

    board->getSquare(start.x, start.y).setPiece(nullptr);
    if (board->getSquare(end.x, end.y).getPiece())
    {
        board->getSquare(end.x, end.y).setPiece(nullptr);
    }
    board->getSquare(end.x, end.y).setPiece(promotingTo);
    promotingTo->setHasMoved(true);
}

bool Move::castleMove() {
    //cout << "entering castle move" << endl;
    Square starting = board->getSquare(start.x, start.y);
    // Square ending = board->getSquare(end.x, end.y);
    Piece *moving = starting.getPiece();
    //cout << moving->getColour() << " =/= " << colour << endl;
    Piece *castle;
    board->getSquare(start.x, start.y).setPiece(nullptr);
    if (start.y + 2 == end.y) { //king side castle
        if (moving->getColour() == "white") {
            castle = board->getSquare(7,7).getPiece();
            board->getSquare(7, 7).setPiece(nullptr);
            board->getSquare(7, 5).setPiece(castle);
        } else {
            castle = board->getSquare(0,7).getPiece();
            board->getSquare(0, 7).setPiece(nullptr);
            board->getSquare(0, 5).setPiece(castle);
        }
    } else {
        if (moving->getColour() == "white") {
            //cout << "right one" << endl;
            castle = board->getSquare(7,0).getPiece();
            board->getSquare(7, 0).setPiece(nullptr);
            board->getSquare(7, 3).setPiece(castle);
        } else {
            castle = board->getSquare(0,0).getPiece();
            board->getSquare(0, 0).setPiece(nullptr);
            board->getSquare(0, 3).setPiece(castle);
        }
    }
    if (castle->gethasMoved())
    {
        return false;
    }
    board->getSquare(end.x, end.y).setPiece(moving);
    moving->setHasMoved(true);
    return true;
}

void Move::enpassantMove() {
    Square starting = board->getSquare(start.x, start.y);
    // Square ending = board->getSquare(end.x, end.y);
    Piece *moving = starting.getPiece();
    // cout << moving->getColour() << " =/= " << colour << endl;
    board->getSquare(start.x, start.y).setPiece(nullptr);
    board->getSquare(start.x, end.y).setPiece(nullptr);
    board->getSquare(end.x, end.y).setPiece(moving);
    moving->setHasMoved(true);
}

// Move::~Move() {}
