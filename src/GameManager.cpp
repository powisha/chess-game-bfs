
#include <iostream>
#include "../include/GameManager.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/MoveValidator.hpp"
#include "../include/Portal.hpp"
#include <vector>
#include <stack>
#include <queue>

GameManager::GameManager(ChessBoard& board, MoveValidator& validator, int maxTurns, vector<Portal*>& Portals)
    : board(board), validator(validator), maxTurns(maxTurns), currentTurn(1),Portals(Portals){}

void GameManager::startGame()
{
    stack<Piece> CapturedPieceHistoryWhite;
    stack<Piece> MovedPieceHistoryWhite;
    stack<pair<int,int>> CapturedPlacesWhite;
    stack<pair<int,int>> MovedPlacesWhite;
    stack<Piece> CapturedPieceHistoryBlack;
    stack<Piece> MovedPieceHistoryBlack;
    stack<pair<int,int>> CapturedPlacesBlack;
    stack<pair<int,int>> MovedPlacesBlack;
    queue <pair<Portal*,int>> Cooldown;

    currentPlayer = "white";
    std::cout << "Starting game..." << std::endl;

    currentTurn = 1;
    std::cout << "Welcome to the game!" << std::endl;

    while (currentTurn <= maxTurns) {

        Piece currentPiece;
        Piece targetPiece;
        int queuesize= Cooldown.size();
        for(int i=0;i<queuesize;i++){

          auto front=Cooldown.front();
          Cooldown.pop();
          front.second--;
          if(front.second>0){
            Cooldown.push(front);}
          }
        board.printBoard();
        std::cout << std::endl;

        string command;
        std::cout << currentPlayer
                  << "'s turn. Please make a move or undo or exit. To move a piece please write it as 'move fromx,fromy tox,toy' where fromx, fromy, tox, toy are integers."
                  << std::endl;
        std::getline(cin, command);

        if (command == "exit" || command == "Exit") {
            cout << "Exiting...GoodBye!" << endl;
            break;
        }
        else if (command == "Undo" || command == "undo") {
            if (currentPlayer == "white") {
                if (MovedPieceHistoryWhite.empty()) {
                    cout << "You can not undo!" << endl;
                }
                else {

                  Piece movedPiece=MovedPieceHistoryWhite.top();
                  Piece capturedPiece=CapturedPieceHistoryWhite.top();
                  int fromx=MovedPlacesWhite.top().first;
                  int fromy=MovedPlacesWhite.top().second;
                  int tox=CapturedPlacesWhite.top().first;
                  int toy=CapturedPlacesWhite.top().second;
                    if (board.isEmpty(fromx,fromy)){

                        board.movePiece(tox,toy,fromx,fromy);

                        board.addPiece(fromx,fromy,movedPiece);
                        if(capturedPiece.type!="Empty"){
                          board.addPiece(tox,toy,capturedPiece);
                         }

                         MovedPieceHistoryWhite.pop();
                         CapturedPieceHistoryWhite.pop();
                         MovedPlacesWhite.pop();
                         CapturedPlacesWhite.pop();

                        currentTurn--;
                        currentPlayer = "black";
                        if(isGameOver(currentPlayer)){
                          cout<<"Game Over! White is Winner!"<<endl;
                          break;}
                    }
                    else {
                        cout << "You can not undo!" << endl;
                    }
                }
            }
            else {
                if (MovedPieceHistoryBlack.empty()) {
                    cout << "You can not undo!" << endl;
                }
                else {

                  Piece movedPiece=MovedPieceHistoryBlack.top();
                  Piece capturedPiece=CapturedPieceHistoryBlack.top();
                  int fromx=MovedPlacesBlack.top().first;
                  int fromy=MovedPlacesBlack.top().second;
                  int tox=CapturedPlacesBlack.top().first;
                  int toy=CapturedPlacesBlack.top().second;
                    if (board.isEmpty(fromx,fromy)){

                       board.movePiece(tox,toy,fromx,fromy);


                        if(capturedPiece.type!="Empty"){
                          board.addPiece(tox,toy,capturedPiece);
                         }

                         MovedPieceHistoryBlack.pop();
                         CapturedPieceHistoryBlack.pop();
                         MovedPlacesBlack.pop();
                         CapturedPlacesBlack.pop();

                        currentTurn--;
                        currentPlayer = "white";
                        if(isGameOver(currentPlayer)){
                          cout<<"Game Over! Black is Winner!"<<endl;
                          break;}
                    }
                    else {
                        cout << "You can not undo!" << endl;
                    }
                }
            }
            continue;
        }
        else {
            int fromx = command[5] - '0';
            int fromy = command[7] - '0';
            int tox   = command[9] - '0';
            int toy   = command[11] - '0';

            if (board.isEmpty(fromx, fromy)) {
                std::cout << "Invalid move!Empty place." << std::endl;
                continue;
            }

            currentPiece = board.getPieceAt(fromx, fromy);
            if (currentPiece.color != currentPlayer) {
                std::cout << "You can't move that piece! Choose another one."
                          << std::endl;
                continue;
            }

            if (validator.isValidMove(fromx, fromy, tox, toy, board)) {

                Piece targtpiece=board.getPieceAt(tox,toy);

                board.movePiece(fromx, fromy, tox, toy);
                cout << currentPlayer << " moved the " << currentPiece.type
                     << " from " << board.key(fromx, fromy)
                     << " to the place " << board.key(tox, toy) << std::endl;

              bool portalused=false;
              Portal* usedPortal=nullptr;
              for (Portal* port: Portals){
                if(port->getin().x==tox && port->getin().y==toy){
                  if(port->isAvailable(board,currentPiece,Cooldown))
                  {
                    usedPortal=port;
                    portalused = port->PortalUse(board,currentPiece,port,Cooldown);
                }
                }
              }

              if(!portalused){

                  if (currentPlayer == "white") {
                    MovedPieceHistoryWhite.push(
                        board.getPieceAt(tox, toy));
                    CapturedPieceHistoryWhite.push(targtpiece);
                    MovedPlacesWhite.push(make_pair(fromx, fromy));
                    CapturedPlacesWhite.push(make_pair(tox, toy));
                }

                 else {
                    MovedPieceHistoryBlack.push(
                        board.getPieceAt(tox, toy));
                    CapturedPieceHistoryBlack.push(
                       targtpiece);
                    MovedPlacesBlack.push(make_pair(fromx, fromy));
                    CapturedPlacesBlack.push(make_pair(tox, toy));
                }
                }

                if(currentPlayer=="white") currentPlayer="black";
                else if(currentPlayer=="black") currentPlayer="white";

                if(isGameOver(currentPlayer)){
                          cout<<"Game Over!"<< currentPlayer <<" lost the game!"<<endl;
                          break;
                }


            }
            else {
                std::cout << "Invalid move!" << std::endl;
                continue;
            }

            currentTurn++;
        }
    }
}

bool GameManager::isGameOver(string color){

  bool isMate=false;

  vector<pair<int,int>> threateningPieces;
  pair<int,int> KingLoc;

  for(int x=0;x<8;x++){
    for(int y=0;y<8;y++){
      if( board.getPieceAt(x,y).color==color && board.getPieceAt(x,y).type=="King"){
        KingLoc=make_pair(x,y);
      }
    }
  }
  for(int w=0;w<8;w++){
    for(int z=0;z<8;z++){
      Piece checkPiece=board.getPieceAt(w,z);
      if(checkPiece.color!=color){
        if(validator.isValidMove(w,z,KingLoc.first,KingLoc.second,board)){
          isMate=true;
          threateningPieces.push_back(make_pair(w,z));
        }
      }
    }
  }

  if(isMate){

    string WkingKey=board.key(KingLoc.first,KingLoc.second);
    unordered_map<string,vector<string>> adjList= validator.makeadjlist(KingLoc.first,KingLoc.second,board);

    for(const auto& x: adjList[WkingKey]){
      int tox= x[0]-'0';
      int toy= x[2]-'0';

      bool threat=false;
    for(const auto& y: threateningPieces){

      if(validator.isValidMove(y.first,y.second,tox,toy,board)){
        threat=true;
        break;}
      }

      if(!threat && board.getPieceAt(tox,toy).color!=color){
        return false;
      }
      }

      if(threateningPieces.size()==1){
        auto w=threateningPieces[0];
        for( int j=0;j<8;j++){
          for(int k=0;k<8;k++){
            Piece current=board.getPieceAt(j,k);
            if (board.getPieceAt(j,k).color==color){
              auto adj=validator.makeadjlist(j,k,board);
              for( const auto& c: adj[board.key(j,k)]){
                int tox=c[0] -'0';
                int toy=c[2] -'0';
                if(w.first==tox && w.second==toy){
                  return false;
                }
              }
            }
          }
        }
      }
      return true;
  }
  return false;
}













