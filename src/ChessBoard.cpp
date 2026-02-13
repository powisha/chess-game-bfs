#include <nlohmann/json.hpp>
#include "ChessBoard.hpp"
#include <unordered_map>
#include <iostream>

using json = nlohmann::json;
using namespace std;

string ChessBoard::key(int x, int y) const
{
    return to_string(x) + "," + to_string(y);
}


void ChessBoard::addPiece(int x, int y, const Piece& piece)
{
    board[key(x,y)]=piece;

}



void ChessBoard::movePiece(int x1, int y1, int x2, int y2)
{
    board[key(x2,y2)]=board[key(x1,y1)];
    board.erase(key(x1,y1));
}

void ChessBoard::printBoard() const
{

    for (int y=7;y>=0;y--)
    {
        std::cout<<y<<" ";
        for (int x=0;x<8;x++){

        if (!board.count(key(x,y))){
            std::cout<<". ";
        }
            else
            {
                const Piece& piece=board.at(key(x,y));
                if (piece.type=="Pawn" && piece.color=="white") std::cout<<"P ";
                else if (piece.type=="Pawn" && piece.color=="black") std:: cout<<"p ";
                else if (piece.type=="King" && piece.color=="white") std::cout<<"K ";
                else if (piece.type=="King" && piece.color=="black") std::cout<<"k ";
                else if (piece.type=="Bishop" && piece.color=="white") std::cout<<"B ";
                else if (piece.type=="Bishop" && piece.color=="black") std::cout<<"b ";
                else if (piece.type=="Rook" && piece.color=="white") std::cout<<"R ";
                else if (piece.type=="Rook" && piece.color=="black") std::cout<<"r ";
                else if (piece.type=="Queen" && piece.color=="white") std::cout<<"Q ";
                else if (piece.type=="Queen" && piece.color=="black") std::cout<<"q ";
                else if (piece.type=="Knight" && piece.color=="white") std::cout<<"N ";
                else if (piece.type=="Knight" && piece.color=="black") std:: cout<<"n ";

            }

        }
        std::cout<<std::endl;

    }

    cout<<"  ";
    for (int x=0;x<8;x++)
    {
        cout<<x<<" ";
    }
}

bool ChessBoard::isEmpty(int x,int y) const
{
    if (board.count(key(x,y)))
    {
        return false;
    }

    else return true;
}

Piece ChessBoard::getPieceAt(int x,int y) const
{
    string pos= key(x,y);

    if (board.count(pos))
    {
        return board.at(pos);
    }

    else return Piece("Empty", "none", {},{});

}

void ChessBoard::removePiece(int x,int y)
{
    if (!isEmpty(x,y))
    {
        board.erase(key(x,y));
    }

}




//
// Created by Sümeyye Nur Doğan on 1.05.2025.
//

