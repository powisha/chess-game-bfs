#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <unordered_map>
#include <string>
#include "Piece.hpp"
using namespace std;

class ChessBoard {
public:
    void addPiece(int x, int y, const Piece& piece);
    void movePiece(int x1, int y1, int x2, int y2);
    void printBoard() const;
    string key(int x, int y) const ;
    bool isEmpty(int x,int y) const;
    Piece getPieceAt(int x,int y) const;
    void removePiece(int x,int y);


private:
    unordered_map<std::string, Piece> board;



};

#endif
