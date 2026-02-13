//
// Created by Sümeyye Nur Doğan on 4.05.2025.
//

#include "ChessBoard.hpp"
#include "Piece.hpp"
#ifndef MOVEVALIDATOR_HPP
#define MOVEVALIDATOR_HPP
using namespace std;

class MoveValidator
{
public:
    MoveValidator(const ChessBoard& board);

    bool isValidMove(int x1,int y1,int x2, int y2, const ChessBoard& board);
    unordered_map<string,vector<string>> makeadjlist(int x1,int y1,const ChessBoard& board);



private:

    const ChessBoard& board;

};

#endif //MOVEVALIDATOR_HPP
