#include <iostream>
#include <iomanip>
#include "display.h"
using namespace std;

Display::~Display() {}

void Display::printBoard(Board *b) {
    int rowNum = 8;
    for (int i = 0; i < 8; i++)
    {
        cout << rowNum << " |";
        rowNum--;
        for (int j = 0; j < 8; j++)
        {
            printSquare(i, j, b->getSquare(i, j));
        }
        cout << "|" << endl;
    }
    cout << "\n   abcdefgh\n" << endl;
}

void Display::printSquare(int x, int y, Square s)
{
    Piece *p = s.getPiece();
    if (p == nullptr) {
        if ((x + y) % 2 == 0) {
            cout << ' ';
        } else {
            cout << '_';
        }
    }
    else {
        string type = p->getType();
        char piece = ' ';
        if (type == "pawn") {
            piece = 'p';
        } else if (type == "bishop") {
            piece = 'b';
        } else if (type == "rook") {
            piece = 'r';
        } else if (type == "knight") {
            piece = 'n';
        } else if (type == "queen") {
            piece = 'q';
        } else if (type == "king") {
            piece = 'k';
        }

        //Capitalize
        string colour = p->getColour();
        if (colour == "white")
        {
            piece += ('A' - 'a');
        }
        cout << piece;
    }
}

void Display::printMsg(string msg) {
    cout << msg << endl;
}

void Display::printScore(int p1score, int p2score) {
    cout << "Final Score:" << endl;
    cout << "White: " << p1score << endl;
    cout << "Black: " << p2score << endl;
}

void Display::printHelp() {
    cout << "------------------------COMMAND LIST------------------------" << endl;
    cout << "Move a human player piece:" << "\t\t" << "move <start> <end>" << endl;
    cout << "Play a pawn promotion move:" << "\t\t" << "move <start> <end> <type>" << endl;
    cout << "Move a computer player piece:" << "\t\t" << "move" << endl;
    cout << "Resign from game:" << "\t\t\t" << "resign" << endl;
    cout << "Show command list" << "\t\t\t" << "help\n" << endl;
}
