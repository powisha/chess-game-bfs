
#include "MoveValidator.hpp"
#include "ChessBoard.hpp"
#include "Piece.hpp"
#include <unordered_map>
#include "GameManager.hpp"
#include "unordered_set"
#include <iostream>

using namespace std;

MoveValidator::MoveValidator(const ChessBoard& b) : board(b){}

 unordered_map<string,vector<string>> MoveValidator::makeadjlist(int x1,int y1,const ChessBoard& board)
{
    Piece piece= board.getPieceAt(x1,y1);
    {
        Piece piece= board.getPieceAt(x1,y1);

        unordered_map<string,vector<string>> adjlist;

        if (board.getPieceAt(x1,y1).type!="Empty")
        {
            if (piece.movement.forward>0)
            {
                int forward= piece.movement.forward;
                string currentkey= board.key(x1,y1);

                for (int y=1;y<=forward;y++)
                {
                    int newy;
                    if (piece.color=="black")
                    {
                        newy=y1-y;
                    }
                    else if (piece.color=="white") newy=y1+y;

                    if ( newy<0 || newy>7) break;
                    if (board.getPieceAt(x1,newy).type=="Empty")
                    {
                        adjlist[currentkey].push_back(board.key(x1,newy));
                    }
                    else if (board.getPieceAt(x1,newy).color!=board.getPieceAt(x1,y1).color && piece.type!="Pawn")
                    {
                        adjlist[currentkey].push_back(board.key(x1,newy));
                        break;
                    }
                    else break;
                }
                if (piece.type!="Pawn")
                {
                    for (int x=1;x<=forward;x++)
                    {
                        int newy2;
                        if (piece.color=="black")
                        {
                            newy2=y1+x;
                        }
                        else if (piece.color=="white") newy2=y1-x;

                        if ( newy2<0 || newy2>7) break;

                        if (board.getPieceAt(x1,newy2).type=="Empty")
                        {
                            adjlist[currentkey].push_back(board.key(x1,newy2));
                        }
                        else if (board.getPieceAt(x1,newy2).color!=board.getPieceAt(x1,y1).color)
                        {
                            adjlist[currentkey].push_back(board.key(x1,newy2));
                            break;
                        }
                        else break;
                    }
                }
            }
                if (piece.movement.diagonal>0)
                {
                    int diag = piece.movement.diagonal;
                    {
                    string currentkey=board.key(x1,y1);
                    for (int y=1;y<=diag;y++)
                    {
                        int newy=y1-y;
                        int newx=x1-y;

                        if (newy<0 || newx<0) break;

                        if (board.getPieceAt(newx,newy).type=="Empty")
                        {
                            adjlist[currentkey].push_back(board.key(newx,newy));
                        }
                        else if (board.getPieceAt(newx,newy).color!=board.getPieceAt(x1,y1).color)
                        {
                            adjlist[currentkey].push_back(board.key(newx,newy));
                            break;
                        }
                        else break;
                    }
                }
                {
                    string currentkey=board.key(x1,y1);
                    for (int y=1;y<=diag;y++)
                    {
                        int newy= y1-y;
                        int newx= x1+y;

                        if (newy<0 || newx>7) break;

                        if (board.getPieceAt(newx,newy).type=="Empty")
                        {
                            adjlist[currentkey].push_back(board.key(newx,newy));

                        }
                        else if (board.getPieceAt(newx,newy).color!=board.getPieceAt(x1,y1).color)
                        {
                            adjlist[currentkey].push_back(board.key(newx,newy));
                            break;
                        }
                        else break;
                    }
                }

                {
                        string currentkey=board.key(x1,y1);
                        for (int y=1;y<=diag;y++)
                            {
                            int newy= y1+y;
                            int newx= x1-y;

                            if (newy>7 || newx<0) break;

                            if (board.getPieceAt(newx,newy).type=="Empty")
                                {
                                adjlist[currentkey].push_back(board.key(newx,newy));

                                }

                            else if (board.getPieceAt(newx,newy).color!=board.getPieceAt(x1,y1).color)
                                {
                                adjlist[currentkey].push_back(board.key(newx,newy));
                                break;
                                }
                            else break;
                            }
                }
                {
                        string currentkey=board.key(x1,y1);
                        for (int y=1;y<=diag;y++)
                        {
                            int newy=y1+y;
                            int newx=x1+y;
                            if (newy>7 || newx>7) break;
                            if (board.getPieceAt(newx,newy).type=="Empty")
                            {
                                adjlist[currentkey].push_back(board.key(newx,newy));

                            }
                            else if (board.getPieceAt(newx,newy).color!=board.getPieceAt(x1,y1).color)
                            {
                                adjlist[currentkey].push_back(board.key(newx,newy));
                                break;
                            }
                            else break;
                        }
                }
                }
            if (piece.movement.sideways>0)
            {
                int sideways=piece.movement.sideways;
                string currentkey=board.key(x1,y1);

                for (int x=1;x<=sideways;x++){
                    int newx1=x1-x;
                    if (newx1<0) break;

                    if (board.getPieceAt(newx1,y1).type=="Empty")
                    {
                        adjlist[currentkey].push_back(board.key(newx1,y1));
                    }
                    else if (board.getPieceAt(newx1,y1).color!=board.getPieceAt(x1,y1).color) //YEME DURUMU
                    {
                        adjlist[currentkey].push_back(board.key(newx1,y1));
                        break;
                    }
                    else break;
                }
                string currentkeyy=board.key(x1,y1);
                for (int x=1;x<=sideways;x++){
                    int newx= x1+x;
                    if (newx>7) break;
                    if (board.getPieceAt(newx,y1).type=="Empty")
                    {
                        adjlist[currentkeyy].push_back(board.key(newx,y1));
                    }
                    else if (board.getPieceAt(newx,y1).color!=piece.color)
                    {
                        adjlist[currentkeyy].push_back(board.key(newx,y1));
                        break;
                    }

                    else break;
                }
            }
            if (piece.movement.diagonal_capture>0)
            {
                int x= piece.movement.diagonal_capture;
                int newx=x1+x;
                int newy1=y1-x;
                int newx2=x1-x;
                int newy2=y1+x;

                if (piece.color=="black")
                {
                    if (newx<=7 &&newy1<=7 && newx>=0 && newy1>=0)
                    {
                        if (board.getPieceAt(newx,newy1).type!="Empty" && board.getPieceAt(newx,newy1).color=="white")
                        {
                            adjlist[board.key(x1,y1)].push_back(board.key(newx,newy1));
                        }
                    }
                    if (newx2<=7 &&newy1<=7 && newx2>=0 && newy1>=0)
                    {
                        if (board.getPieceAt(newx2,newy1).type!="Empty" && board.getPieceAt(newx2,newy1).color=="white")
                        {
                            adjlist[board.key(x1,y1)].push_back(board.key(newx2,newy1));
                        }
                    }
                }
                else if (piece.color=="white")
                {
                    if (newx<=7 &&newy2<=7 && newx>=0 && newy2>=0)
                    {
                        if (board.getPieceAt(newx,newy2).type!="Empty" && board.getPieceAt(newx,newy2).color=="black")
                        {
                            adjlist[board.key(x1,y1)].push_back(board.key(newx,newy2));
                        }
                    }
                    if(newx2<=7 &&newy2<=7 && newx2>=0 && newy2>=0)
                    {
                        if (board.getPieceAt(newx2,newy2).type!="Empty" && board.getPieceAt(newx2,newy2).color=="black")
                        {
                            adjlist[board.key(x1,y1)].push_back(board.key(newx2,newy2));
                        }
                    }
                }
            }
            if (piece.movement.first_move_forward>0)
            {
                if (piece.firstx==x1 && piece.firsty==y1)
                {
                    string currentkey=board.key(x1,y1);
                    for (int i=1; i<=piece.movement.first_move_forward;i++)
                    {
                        if (piece.color=="white")
                        {
                            int newy=y1+i;
                            if (board.isEmpty(x1,newy))
                            {
                                adjlist[board.key(x1,y1)].push_back(board.key(x1,newy));
                            }
                            else break;
                        }
                        else if (piece.color=="black")
                        {
                            int newy=y1-i;

                            if (board.isEmpty(x1,newy))
                            {
                                adjlist[board.key(x1,y1)].push_back(board.key(x1,newy));
                            }
                            else break;
                        }
                    }
                }

            }
            if (piece.movement.l_shape==true)
            {
                vector<pair<int,int>> knightmoves={{1,2},{-1,2},{1,-2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};

                for (const auto& [dx,dy] : knightmoves)
                {
                    int firstx=1;
                    int firsty=1;
                    int i=0;
                    int j=0;
                    if (dx<0) i=-1;
                    else if (dx>0) i=1;
                    if (dy<0) j=-1;
                    else if (dy>0) j=1;
                    if (x1+dx<0 || x1+dx>7 || y1+dy<0 || y1+dy>7) continue;
                    if (!piece.special_abilities.jump_over)
                    {
                        for (int x=1;x<=abs(dx);x++)
                        {
                            if (!board.isEmpty(x1+x*i,y1)){
                                firstx=0;
                                break;
                            }
                        }
                        if (firstx)
                        {
                            for (int y=1;y<=abs(dy);y++)
                            {
                                if (!board.isEmpty(x1+dx,y1+j*y))
                                {
                                    firstx=0;
                                    break;
                                }
                            }
                        }

                        for (int y=1;y<=abs(dy);y++)
                        {
                            if (!board.isEmpty(x1,y1+j*y))
                            {
                                firsty=0;
                                break;
                            }
                        }
                        if (firsty)
                        {
                            for (int x=1;x<=abs(dx);x++)
                            {
                                if (!board.isEmpty(x1+x*i,y1+dy))
                                {
                                    firsty=0;
                                    break;
                                }
                            }
                        }
                        if (firstx || firsty){
                            adjlist[board.key(x1,y1)].push_back(board.key(x1+dx,y1+dy));
                        }
                    }

                    else if (piece.special_abilities.jump_over)
                    {
                        if (!board.isEmpty(x1+dx,y1+dy))
                        {
                            Piece target= board.getPieceAt(x1+dx,y1+dy);
                            if (target.color!=piece.color)
                            {
                                adjlist[board.key(x1,y1)].push_back(board.key(x1+dx,y1+dy));
                            }
                        }
                        else
                        {
                            adjlist[board.key(x1,y1)].push_back(board.key(x1+dx,y1+dy));
                        }
                    }

                }
            }
        }
        return adjlist;
    }
}

bool MoveValidator::isValidMove(int x1,int y1,int x2,int y2, const ChessBoard& board)
{
    string start= board.key(x1,y1);
    string target= board.key(x2,y2);

    queue <string> q;
    unordered_set<string> visited;
    visited.insert(start);
    q.push(start);
    unordered_map<string, vector<string>> adjListt;

    while (!q.empty())
    {
        string current=q.front();
        q.pop();
        int cx = current[0] - '0';
        int cy = current[2] - '0';
        adjListt= makeadjlist(cx,cy,board);

        if (current==target)
        {
            return true;
        }

        for (const auto& neigh:adjListt[current])
        {
            if (!visited.count(neigh))
            {
                q.push(neigh);
                visited.insert(neigh);
            }
        }
    }
    return false;
}

