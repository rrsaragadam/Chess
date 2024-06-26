#include "game.h"
#include "human.h"
#include "player.h"
#include "computer.h"
#include "square.h"
#include "move.h"
#include "normalmove.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Game::Game(Display *d) : display{d} {}

Game::~Game() {
    delete display;
    delete board;
    delete player1;
    delete player2;
}

void Game::play() {
    display->printMsg("Play a normal game:\tgame <human/computer[1-4+]> <human/computer[1-4+]>\nStart setup mode:\tsetup\n");
    string com;
    string command;
    cin >> command;
    while(true) {
        if (command == "game") {
            board = new Board("normal");
            break;
        }
        else if (command == "setup") {
            board = new Board{"setup"};
            setup();
            display->printMsg("Choose your players:\t\t<human/computer[1-4+]> <human/computer[1-4+]>");
            break;
        }
        else {
            display->printMsg("Error invalid command, please try again!");
        }
    }
    initGame();
    display->printMsg("\nWelcome to Chess!\n");
    display->printHelp();
    display->printBoard(board);
    Player *currPlayer;
    if ((turn % 2) != 0) {
            currPlayer = player1;
        } else {
            currPlayer = player2;
        }
    string name = currPlayer->getName();
    string colour = currPlayer->getColour();
    string msg = "It's " + name + "'s turn! (" + colour + ")";
    display->printMsg(msg);
    //TESTINGGGG
    // //cout << "THE POssible:" << board->isMovePossible("white");
    string line;
    while (getline(cin, line)) {
        //cout << "running play game" << endl;
        istringstream ss{line};
        ss >> command;
        //cout << "Command given:  " << command << endl;
        if (command == "help") {
            display->printHelp();
            continue;
        }  
        else if (command == "move") {
            string startPos, endPos, upgrade;
            ss >> startPos >> endPos >> upgrade;
            move(startPos, endPos, upgrade);
            if (turn == 0) {
                display->printMsg("Thanks for playing!");
                return;
            }
            continue;
        }
        else if (command == "resign") {
            if (turn % 2 != 0) {
                display->printMsg("White resigns! Thanks for playing!");
            } else {
                display->printMsg("Black resigns! Thanks for playing!");
            }
            return;
        }
    }
}

void Game::setup() {
    display->printMsg("\nAdd piece\t\t+ <Piece> <Square>");
    display->printMsg("Remove piece\t\t- <Square>");
    display->printMsg("Set next colour\t\t= <Colour>");
    display->printMsg("Finish setup\t\tdone\n");
    string cmd;
    string colour;
    string square;
    char piece;
    while (1) {
            cin >> cmd;
            if (cmd == "done") {
                // cout << "STATE " << board->getState() << endl;
                board->getMovesPossible("white");
                int retval = board->isValid();
                if (retval == 0) {
                    display->printMsg("Set up complete!\n");
                    display->printBoard(board);
                    break;
                } else {
                    if (retval == 1) {
                        display->printMsg("Invalid board: One king of each colour necessary. Please configure again.\n");
                    } else if (retval == 2) {
                        display->printMsg("Invalid board: Pawn on first or last row. Please configure again.\n");
                    } else {
                        display->printMsg("Invalid board: King is in check. Please configure again.\n");
                    }
                    display->printBoard(board);
                    continue;
                }
            } 
            else if (cmd == "+") {
                cin >> piece;
                cin >> square;
                addPiece(piece, square);
            }
            else if (cmd == "-") {
                cin >> square;
                removePiece(square);
            } 
            else if (cmd == "=") {
                cin >> colour;
                if (colour == "white") {
                    turn = 1;
                    display->printMsg("White will start!\n");
                } else {
                    turn = 2;
                    display->printMsg("Black will start!\n");
                }
            }
        } 
}

void Game::initGame() {
    string name1;
    string name2;
    string w_player;
    string b_player;
    while (1) {
        cin >> w_player;
        cin >> b_player;
        if ((w_player == "human" || w_player.substr(0, 8) == "computer") && (b_player == "human" || b_player.substr(0, 8) == "computer")) {
            break;
        } else {
            display->printMsg("Incorrect input. Enter it in the form:");
            display->printMsg("<human/computer[1-4+]> <human/computer[1-4+]>");
        }
    }
    display->printMsg("Enter player1's name:");
    cin >> name1;
    if (w_player == "human")
    {
        player1 = new Human{"white", name1};
    }
    else if (w_player.substr(0, 8) == "computer")
    {
        char levl = w_player[9];
        int level = levl - '0';
        player1 = new Computer{level, "white", name1};
    }
    display->printMsg("Enter player2's name:");
    cin >> name2;
    if (b_player == "human")
    {
        player2 = new Human{"black", name2};
    }
    else if (b_player.substr(0, 8) == "computer")
    {
        char levl = b_player[9];
        int level = levl - '0';
        player2 = new Computer{level, "black", name2};
    }
}

void Game::addPiece(char piece, string square) {
    //Find the x,y coordinates
    int x = abs((square[1] - '1')-7);
    int y = square[0] - 'a';

    if (!isValidPos(square)) {
        return;
    }

    //Find the piece & colour
    string colour;
    if (piece >= 'a' && piece <= 'z') {
        colour = "black";
        piece += ('A' - 'a');
    } else {
        colour = "white";
    }

    //Add the piece
    if (piece == 'K') {
        King *k = new King{colour};
        board->getSquare(x, y).setPiece(k);
    }
    else if (piece == 'Q') {
        Queen *q = new Queen{colour};
        board->getSquare(x, y).setPiece(q);
    }
    else if (piece == 'N') {
        Knight *n = new Knight{colour};
        board->getSquare(x, y).setPiece(n);
    }
    else if (piece == 'R') {
        Rook *r = new Rook{colour};
        board->getSquare(x, y).setPiece(r);
    }
    else if (piece == 'B') {
        Bishop *b = new Bishop{colour};
        board->getSquare(x, y).setPiece(b);
    }
    else if (piece == 'P') {
        Pawn *p = new Pawn{colour};
        board->getSquare(x, y).setPiece(p);
    } else {
        display->printMsg("Not a valid piece. Try again.");
        return;
    }
    display->printBoard(board); 
}


    void Game::removePiece(string square) {
    int x = abs((square[1] - '1')-7);
    int y = square[0] - 'a';
    if (!isValidPos(square)) {
        return;
    }
    board->getSquare(x, y).setPiece(nullptr);
    display->printBoard(board); 
    }

    void Game::move(string startPos, string endPos, string upgrade) {
    Player *currPlayer;
    // cout << "Turn count: " << turn << endl;
    if ((turn % 2) != 0) {
        currPlayer = player1;
    } else {
        // cout << "here????????" << endl;
        currPlayer = player2;
    }
    //human move
    if (dynamic_cast<Human *>(currPlayer)) {
        // cout << "THIS IS A HUMAN" << endl;
        if (!isValidPos(startPos) || !isValidPos(endPos)) {
            return;
        }
        int startx = abs((startPos[1] - '1')-7);
        int starty = startPos[0] - 'a';
        int endx = abs((endPos[1] - '1')-7);
        int endy = endPos[0] - 'a';

        Position start{startx, starty};
        Position end{endx, endy};
        Move theMove{board, start, end, currPlayer->getColour()};
        string moveType = theMove.getMoveType();
        if (moveType == "enpassant") {
            theMove.enpassantMove();
        } 
            if (moveType == "castle") {
            if (board->getSquare(start.x, start.y).getPiece()->gethasMoved()) {
                display->printMsg("Not a valid move. Try again!");
            }
                bool rookMove = theMove.castleMove(); //return true if rook hasn't moved before and false otherwise
                if (!rookMove) {
                    display->printMsg("Not a valid move. Try again!");
                }
        }
        if (moveType == "promotepawn") {
            //display->printMsg("What would you like to promote the pawn to: <rook, knight, bishop, queen>");
            //string promote;
            //cin >> promote;
                if (upgrade != "rook" && upgrade != "knight" && upgrade != "bishop" && upgrade != "queen") {
                    display->printMsg("Invalid piece, please try again!");
                } else {
                    theMove.promoteMove(upgrade);
                }
        }
        else if (moveType == "normalkill") {
            theMove.killMove();
        } else if (moveType == "normalmove") {
            // cout << "in the normal move" << endl;
            if (board->getSquare(start.x, start.y).getPiece()->getType() == "pawn") {
                int wdistance = start.x - end.x;
                int bdistance = end.x - start.x;
                if (board->getSquare(start.x, start.y).getPiece()->gethasMoved() && (wdistance > 1 || bdistance > 1)) {
                    display->printMsg("Not a valid move. Try again!");
                } else {
                    theMove.normalMove();
                }
            } else {
                theMove.normalMove();
            }
        } else if (moveType == "Invalid move") {
            display->printMsg("Invalid Move, try again!");
        }
        if (moveType != "Invalid move") {
            display->printBoard(board);
            string state = board->getState();
            if (state != "normal") {
                if (state == "stalemate") {
                    display->printMsg("Stalemate!");
                    turn = 0;
                } else if (state == "whitecheckmate") {
                    display->printMsg("Checkmate! White wins!");
                    turn = 0;
                } else if (state == "blackcheckmate") {
                    display->printMsg("Checkmate! Black wins!");
                    turn = 0;
                } else if (state == "whitecheck") {
                    display->printMsg("White is in check.");
                } else if (state == "blackcheck") {
                    display->printMsg("Black is in check.");
                }
            }
            if (turn != 0) {
                turn++;
                if ((turn % 2) != 0) {
                    currPlayer = player1;
                } else {
                    currPlayer = player2;
                }
                string name = currPlayer->getName();
                // cout << "entering here" << endl;
                string colour = currPlayer->getColour();
                // cout << "entering her2" << endl;
                string msg = "It's " + name + "'s turn! (" + colour + ")";
                display->printMsg(msg);
            }
        }
    } else {
        // cout << "THIS IS A COMPUTER" << endl;
        Computer *c = dynamic_cast<Computer *>(currPlayer);
        Computer cPlayer{c->getLevel(), c->getColour(), c->getName()};
        pair<Position, Position> compMove = cPlayer.getMove(board);
        int startx = compMove.first.x;
        int starty = compMove.first.y;
        int endx = compMove.second.x;
        int endy = compMove.second.y;
        Position start{startx, starty};
        Position end{endx, endy};
        Move cMove{board, start, end, c->getColour()};

        string moveType = cMove.getMoveType();

        if (moveType == "enpassant")
        {
            cMove.enpassantMove();
        }
        else if (moveType == "castle")
        {
            if (board->getSquare(start.x, start.y).getPiece()->gethasMoved())
            {
                display->printMsg("Not a valid move. Try again!");
            }
            bool rookMove = cMove.castleMove(); // return true if rook hasn't moved before and false otherwise
            if (!rookMove)
            {
                display->printMsg("Not a valid move. Try again!");
            }
        }
        else if (moveType == "promotepawn")
        {
            if (upgrade != "rook" && upgrade != "knight" && upgrade != "bishop" && upgrade != "queen")
            {
                display->printMsg("Invalid piece, please try again!");
            }
            else
            {
                string promote = "queen";
                cMove.promoteMove(promote);
            }
        }
        else if (moveType == "normalkill")
        {
            cMove.killMove();
        }
        else if (moveType == "normalmove")
        {
            if (board->getSquare(start.x, start.y).getPiece()->getType() == "pawn")
            {
                int wdistance = start.x - end.x;
                int bdistance = end.x - start.x;
                if (board->getSquare(start.x, start.y).getPiece()->gethasMoved() && (wdistance > 1 || bdistance > 1))
                {
                    display->printMsg("Not a valid move. Try again!");
                }
                else
                {
                    cMove.normalMove();
                }
            }
            else
            {
                cMove.normalMove();
            }
        }
        else if (moveType == "Invalid move")
        {
            display->printMsg("Invalid Move, try again!");
        }
        if (moveType != "Invalid move")
        {
            display->printBoard(board);
            string state = board->getState();
            if (state != "normal")
            {
                if (state == "stalemate")
                {
                    display->printMsg("Stalemate!");
                    turn = 0;
                }
                else if (state == "whitecheckmate")
                {
                    display->printMsg("Checkmate! White wins!");
                    turn = 0;
                }
                else if (state == "blackcheckmate")
                {
                    display->printMsg("Checkmate! Black wins!");
                    turn = 0;
                }
                else if (state == "whitecheck")
                {
                    display->printMsg("White is in check.");
                }
                else if (state == "blackcheck")
                {
                    display->printMsg("Black is in check.");
                }
            }
            if (turn != 0)
            {
                turn++;
                if ((turn % 2) != 0)
                {
                    currPlayer = player1;
                }
                else
                {
                    currPlayer = player2;
                }
                string name = currPlayer->getName();
                string colour = currPlayer->getColour();
                string msg = "It's " + name + "'s turn! (" + colour + ")";
                display->printMsg(msg);
                
            }
        }
    }
}

bool Game::isValidPos(string square)
{
    int x = abs((square[1] - '1') - 7);
    int y = square[0] - 'a';

    if (x < 0 || x > 7 || y < 0 || y > 7 || square[1] < '1' || square[1] > '8')
    {
        display->printMsg("Not a valid coordinate. Try again.");
        return false;
    }
    return true;
}
    


