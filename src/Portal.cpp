#include "../include/ConfigReader.hpp"
#include "../include/Piece.hpp"
#include "../include/MoveValidator.hpp"
#include "../include/GameManager.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/Portal.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

Portal::Portal(std::string id,
               Position in,
               Position out,
               std::vector<std::string> allowedcolors,
               int cooldown,
               bool preservedir)
    : id(std::move(id)),
      in(in),
      out(out),
      allowedcolors(std::move(allowedcolors)),
      preservedir(preservedir),
      cooldown(cooldown)
{}

string Portal::getid() const{
    return id;}
Position Portal::getin() const {
    return in;}
Position Portal::getout() const {
    return out;}
vector<string> Portal::getallowedcolors() const{
    return allowedcolors;}
int Portal::getcooldown() const {
    return cooldown;
}
bool Portal::getpreservedir() const{
    return preservedir;}

bool Portal::isAvailable(ChessBoard& board, Piece& cpiece,queue <pair<Portal*, int>>& cooldownq ){

  bool colorava=false;

  for(const auto& c: allowedcolors){
    if(cpiece.color==c){
      colorava=true;
      break;}
  }

  if(!colorava){
    return false;
  }

  if(!board.isEmpty(getout().x,getout().y)){
    return false;}

    bool isinqueue=false;
    queue<pair<Portal*, int>> temp;
    while(!cooldownq.empty()){
        if(cooldownq.front().first->getid()==getid()){
          isinqueue=true;
                        }
        temp.push(cooldownq.front());
        cooldownq.pop();
    }

    while(!temp.empty()){
        cooldownq.push(temp.front());
        temp.pop();}

    if(isinqueue) return false;


    return true;


}


bool Portal:: PortalUse(ChessBoard& board,Piece& cpiece,Portal* portal,queue <pair<Portal*, int>>& cooldownq){

  vector<string> colors= portal->getallowedcolors();
  Position enter=portal->getin();

  Position exit=portal->getout();

  if(!portal->isAvailable(board,cpiece,cooldownq)){

    return false;}


    board.movePiece(enter.x,enter.y,exit.x,exit.y);
    cooldownq.push(make_pair(portal,2*(portal->getcooldown())));

    return true;



    }











//
// Created by Sümeyye Nur Doğan on 1.06.2025.
//
