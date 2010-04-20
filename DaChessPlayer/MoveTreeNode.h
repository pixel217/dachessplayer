#pragma once
#include "Move.h"
#include "Board.h"

class MoveTreeNodeList;

class MoveTreeNode
{
public:
    MoveTreeNode(void);
    ~MoveTreeNode(void);
    Move m_move;
    //Board ResultSituation;
    bool isCapture:1;
    char computedDepth:4;
    short value;
    MoveTreeNodeList * NextMoveList;
    bool operator< (const MoveTreeNode& rhs)
    {
        if(value>rhs.value)
            return true;
        if(value<rhs.value)
            return false;
        return (!rhs.isCapture || isCapture);
    }
    unsigned char PlayerSide:2;
    void generateMoves(Board* const playingBoard, bool forceDisplay =false);
    void addMove(Board* const playingBoard, const Position & origin,const Position & destination,bool forceDisplay =false);
    int alphaBeta(int depth,const unsigned char& currentColor,int alpha,int beta, Board * PlayingBoard, bool drawProgress=false, unsigned char depthCounter=0);
};
