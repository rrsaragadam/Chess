#include "computer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

Computer::Computer(int level, std::string colour, std::string name) : Player{colour, name}, level{level} {}

int Computer::getLevel() {
    return level;
}

pair<Position, Position> Computer::getMove(Board *b) {
    if (level == 1) {
        return getLevel1Move(b);
    } else if (level == 2) {
        return getLevel2Move(b);
    } else {
        return make_pair(Position{-1,-1}, Position{-1,-1});
    }
}

pair<Position, Position> Computer::getLevel1Move(Board *b) {
    vector<pair<Position, Position>> allMoves = b->getMovesPossible(getColour());
    // std::random_device rd;
    // std::mt19937 g(rd());
    // shuffle(allMoves.begin(), allMoves.end(), g);
    random_shuffle(allMoves.begin(), allMoves.end());
    for (auto move : allMoves) {
        Position start = move.first;
        Position end = move.second;
        Move tempCheck{b, start, end, getColour()};
        if (tempCheck.isKingSafe()) {
            return move;
        }
    }
    return make_pair(Position{-1,-1}, Position{-1,-1});
}

pair<Position, Position> Computer::getLevel2Move(Board *b) {
    vector<pair<Position, Position>> allMoves = b->getMovesPossible(getColour());
    vector<pair<Position, Position>> checkMoves;
    vector<pair<Position, Position>> killMoves;
    vector<pair<Position, Position>> normalMoves;
    // random_device rd;
    // mt19937 g(rd());
    // shuffle(allMoves.begin(), allMoves.end(), g);
    random_shuffle(allMoves.begin(), allMoves.end());
    for (auto move : allMoves) {
        Position start = move.first;
        Position end = move.second;
        Board cloneBoard = *b;
        Move tempMove{&cloneBoard, start, end, getColour()};
        
        if (tempMove.isKingSafe()) {
            if (tempMove.isEnpassant()) {
                tempMove.enpassantMove(); //do the move, then check if the state of the board is in check
                if (cloneBoard.isCheck(getColour())) {
                    checkMoves.emplace_back(move);
                }
            } 
            else if (tempMove.isPromotepawn()) {
                tempMove.promoteMove("queen"); //do the move, then check if the state of the board is in check
                if (cloneBoard.isCheck(getColour())) {
                    checkMoves.emplace_back(move);
                }
            }
            else if (tempMove.isCastle()) {
                tempMove.castleMove(); //do the move, then check if the state of the board is in check
                if (cloneBoard.isCheck(getColour())) {
                    checkMoves.emplace_back(move);
                }
            }
            else if (tempMove.isNormalKill()) {
                tempMove.killMove(); //do the move, then check if the state of the board is in check
                if (cloneBoard.isCheck(getColour())) {
                    checkMoves.emplace_back(move);
                } else {
                    killMoves.emplace_back(move);
                }
            }
            else {
                normalMoves.emplace_back(move); 
            }
        }
    }
    for(auto move: checkMoves) { //get the first move in checkMoves, if none move on
		return move;
	}
	for(auto move: killMoves) {
		return move;
	}
	for(auto move: normalMoves) {
		return move;
	}
    return getLevel1Move(b);
}


