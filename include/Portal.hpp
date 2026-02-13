#include "ChessBoard.hpp"
#include "ConfigReader.hpp"
#include "Piece.hpp"
#include "MoveValidator.hpp"
#include "GameManager.hpp"
#include <iostream>
using namespace std;






//
// Created by Sümeyye Nur Doğan on 1.06.2025.
//

#ifndef PORTAL_HPP
#define PORTAL_HPP

class Portal{

  public:
    Portal(string id, Position in, Position out, vector<string> allowedcolors,int cooldown,bool preservedir);

    string getid() const;

    Position getin()const;
    Position getout() const;
    vector<string> getallowedcolors() const;
    int getcooldown() const;


    bool getpreservedir() const;

    bool PortalUse(ChessBoard& board,Piece& cpiece,Portal* portal,queue<pair<Portal*, int>>& cooldownq);
    bool isAvailable(ChessBoard& board, Piece& cpiece,queue <pair<Portal*, int>>& cooldownq);
    private:

      string id;
      Position in;
      Position out;
      vector<string> allowedcolors;
      bool preservedir;
      int cooldown;



};

#endif //PORTAL_HPP
