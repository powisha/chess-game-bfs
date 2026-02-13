#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
using namespace std;
#include <string>
#include <vector>
#include <Portal.hpp>

class ChessBoard;
class MoveValidator;

class GameManager {

private:
  ChessBoard& board;
  MoveValidator& validator;
  std::string currentPlayer;
  int maxTurns;
  int currentTurn;
  vector<Portal*> Portals;

  public:

  GameManager(ChessBoard& board, MoveValidator& validator, int maxTurns,vector<Portal*>& Portals);

  void startGame();
  bool isGameOver(string color);
};

#endif // GAMEMANAGER_HPP
