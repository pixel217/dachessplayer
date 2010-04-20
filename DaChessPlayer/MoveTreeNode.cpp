#include "MoveTreeNode.h"
#include "MoveTreeNodeList.h"
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <pthread.h>

extern pthread_mutex_t playerPlayedMutex;

extern bool playerPlayed;
extern int evaluateCalls;
extern int alphaBetaCalls;    
extern int positionsGenerated;
extern int positionsEvaluated;

MoveTreeNode::MoveTreeNode(void)
:isCapture(false)
,value(0)
,computedDepth(-1)
{
    NextMoveList=new MoveTreeNodeList();
}

MoveTreeNode::~MoveTreeNode(void)
{
    delete NextMoveList;
}

void MoveTreeNode::generateMoves(Board* const playingBoard, bool forceDisplay)
{
    char testPosX,testPosY;
    unsigned char currentColor = PlayerSide;
    for (testPosX = 0; testPosX < BOARD_SIZE; testPosX++)
    {
        for (testPosY = 0; testPosY < BOARD_SIZE; testPosY++)
        {
            Position testPos,possibleNewPos;
            testPos.x=testPosX;
            testPos.y=testPosY;
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (PAWN_MASK|currentColor))
            {
                possibleNewPos.x=testPos.x;
                if(currentColor&WHITE)
                {
                    possibleNewPos.y=testPos.y+1;
                }
                else
                {
                    possibleNewPos.y=testPos.y-1;
                }
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x+1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x-1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                if (((testPos.y==1)&&(currentColor&WHITE))||
                    ((testPos.y==BOARD_SIZE-2)&&(currentColor&BLACK)))
                {
                    possibleNewPos.x=testPos.x;
                    if(currentColor&WHITE)
                    {
                        possibleNewPos.y=testPos.y+2;
                    }
                    else
                    {
                        possibleNewPos.y=testPos.y-2;
                    }
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
            }
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (KNIGHT_MASK|currentColor))
            {
                possibleNewPos.y=testPos.y+2;
                possibleNewPos.x=testPos.x+1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x-1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.y=testPos.y-2;
                possibleNewPos.x=testPos.x+1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x-1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x-2;
                possibleNewPos.y=testPos.y+1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.y=testPos.y-1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.x=testPos.x+2;
                possibleNewPos.y=testPos.y-1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                possibleNewPos.y=testPos.y+1;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
            }
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (BISHOP_MASK|currentColor))
            {
                for (int i= -1*BOARD_SIZE+1;i<BOARD_SIZE;i++)
                {
                    possibleNewPos.x=testPos.x+i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x-i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
            }
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (ROOK_MASK|currentColor))
            {
                for (int i= 0;i<BOARD_SIZE;i++)
                {
                    possibleNewPos.x=testPos.x;
                    possibleNewPos.y=i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=i;
                    possibleNewPos.y=testPos.y;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
            }
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (QUEEN_MASK|currentColor))
            {
                for (int i= -1*BOARD_SIZE+1;i<BOARD_SIZE;i++)
                {
                    possibleNewPos.x=testPos.x+i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x-i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
                for (int i= 0;i<BOARD_SIZE;i++)
                {
                    possibleNewPos.x=testPos.x;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x+i;
                    possibleNewPos.y=testPos.y;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
            }
            if (playingBoard->m_board_Data[testPos.x][testPos.y] == (KING_MASK|currentColor))
            {
                for (int i= -1;i<2;i++)
                {
                    possibleNewPos.x=testPos.x+i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x-i;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x;
                    possibleNewPos.y=testPos.y+i;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                    possibleNewPos.x=testPos.x+i;
                    possibleNewPos.y=testPos.y;
                    addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
                /* TODO MANAGE CASTLE MOVE
                if((currentColor==1)&&(ResultSituation.canWhite_LongCastle))||((currentColor==-1)&&(ResultSituation.canBlack_LongCastle))
                {
                possibleNewPos.x=testPos.x-2;
                possibleNewPos.y=testPos.y;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }
                if((currentColor==1)&&(ResultSituation.canWhite_ShortCastle))||((currentColor==-1)&&(ResultSituation.canBlack_ShortCastle))
                {
                possibleNewPos.x=testPos.x+2;
                possibleNewPos.y=testPos.y;
                addMove(playingBoard,testPos,possibleNewPos,forceDisplay);
                }*/

            }
        }
    }
    if(!NextMoveList)
    {
        std::cout << "WTF?!?!" << std::endl;
        exit(0);
    }
}

void MoveTreeNode::addMove( Board* const playingBoard, const Position & origin,const Position & destination,bool forceDisplay /*=false*/ )
{
    if(origin==destination)
        return;
    //la case est hors plateau
    if ((destination.x<0)||(destination.x>(BOARD_SIZE-1))||(destination.y<0)||(destination.y>(BOARD_SIZE-1)))
        return;
    //la case est occupée par une piece de meme couleur
    if (playingBoard->m_board_Data[destination.x][destination.y]&COLOR_MASK&playingBoard->m_board_Data[origin.x][origin.y])
        return;
    //avancer le pion sur une case occupée
    if ((playingBoard->m_board_Data[origin.x][origin.y]&PAWN_MASK)&&(destination.x==origin.x)&&
        (playingBoard->m_board_Data[destination.x][destination.y]))
        return;
    //avancer le pion de 2 alors qu'il y a une m_board_piece dans le chemin
    if ((playingBoard->m_board_Data[origin.x][origin.y]&PAWN_MASK)&&(destination.x==origin.x)
        &&(((destination.y==origin.y-2)&&(playingBoard->m_board_Data[origin.x][origin.y-1]))
        ||((destination.y==origin.y+2)&&(playingBoard->m_board_Data[origin.x][origin.y+1])))) 
        return;
    //prise du pion sans m_board_piece a prendre
    if ((playingBoard->m_board_Data[origin.x][origin.y]&PAWN_MASK)&&(destination.x!=origin.x))
    {
        if(!playingBoard->m_board_Data[destination.x][destination.y])
            return;
        if(!((~playingBoard->m_board_Data[origin.x][origin.y]&COLOR_MASK)==(playingBoard->m_board_Data[destination.x][destination.y]&COLOR_MASK)))
            return;
    }
    //si c'est un fou ou une reine qui va vers le NE les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(BISHOP_MASK|QUEEN_MASK))&&
        (destination.x>origin.x)&&(destination.y>origin.y))
    {
        for (int i=1;i<(destination.y-origin.y);i++)
            if (playingBoard->m_board_Data[origin.x+i][origin.y+i]) return;
    }
    //si c'est un fou ou une reine qui va vers le NW les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(BISHOP_MASK|QUEEN_MASK))&&
        (destination.x<origin.x)&&(destination.y>origin.y))
    {
        for (int i=1;i<(destination.y-origin.y);i++)
            if (playingBoard->m_board_Data[origin.x-i][origin.y+i]) return;
    }
    //si c'est un fou ou une reine qui va vers le SE les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(BISHOP_MASK|QUEEN_MASK))&&
        (destination.x>origin.x)&&(destination.y<origin.y))
    {
        for (int i=1;i<(origin.y-destination.y);i++)
            if (playingBoard->m_board_Data[origin.x+i][origin.y-i]) return;
    }
    //si c'est un fou ou une reine qui va vers le SW les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(BISHOP_MASK|QUEEN_MASK))&&
        (destination.x<origin.x)&&(destination.y<origin.y))
    {
        for (int i=1;i<(origin.y-destination.y);i++)
            if (playingBoard->m_board_Data[origin.x-i][origin.y-i]) return;
    }
    //si c'est une tour ou une reine qui va vers le N les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(ROOK_MASK|QUEEN_MASK))&&
        (destination.x==origin.x)&&(destination.y>origin.y))
    {
        for (int i=1;i<(destination.y-origin.y);i++)
            if (playingBoard->m_board_Data[origin.x][origin.y+i]) return;
    }
    //si c'est une tour ou une reine qui va vers le S les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(ROOK_MASK|QUEEN_MASK))&&
        (destination.x==origin.x)&&(destination.y<origin.y))
    {
        for (int i=1;i<(origin.y-destination.y);i++)
            if (playingBoard->m_board_Data[origin.x][origin.y-i]) return;
    }
    //si c'est une tour ou une reine qui va vers le E les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(ROOK_MASK|QUEEN_MASK))&&
        (destination.x>origin.x)&&(destination.y==origin.y))
    {
        for (int i=1;i<(destination.x-origin.x);i++)
            if (playingBoard->m_board_Data[origin.x+i][origin.y]) return;
    }
    //si c'est une tour ou une reine qui va vers le W les cases sur le chemin doivent etre libres
    if ((playingBoard->m_board_Data[origin.x][origin.y]&(ROOK_MASK|QUEEN_MASK))&&
        (destination.x<origin.x)&&(destination.y==origin.y))
    {
        for (int i=1;i<(origin.x-destination.x);i++)
            if (playingBoard->m_board_Data[origin.x-i][origin.y]) return;
    }

    // si tout est bon, on ajoute le mouvement si on ne l'a pas déjà
    for(std::vector<MoveTreeNode*>::iterator iter = NextMoveList->m_moveNodeList.begin();iter != NextMoveList->m_moveNodeList.end();++iter)
    {
        if(((*iter)->m_move.origin==origin)&&((*iter)->m_move.destination==destination))
            return;
    }
    
    unsigned char undoOri=playingBoard->m_board_Data[origin.x][origin.y];
    unsigned char undoDest=playingBoard->m_board_Data[destination.x][destination.y];
    MoveTreeNode* nextMove = new MoveTreeNode;
    nextMove->m_move.origin=origin;
    nextMove->m_move.destination=destination;
    nextMove->PlayerSide=~PlayerSide&COLOR_MASK;
    bool valid = playingBoard->makeMove(nextMove);
    if(valid)
    {
        if (playingBoard->m_board_Data[destination.x][destination.y]==0)
        {
            nextMove->isCapture=false;
        }
        else
        {
            nextMove->isCapture=true;
        }
        NextMoveList->m_moveNodeList.push_back(nextMove);
    }
    else
    {
        delete nextMove;
    }
    playingBoard->m_board_Data[origin.x][origin.y]=undoOri;
    playingBoard->m_board_Data[destination.x][destination.y]=undoDest;

    return;
}

int MoveTreeNode::alphaBeta(int depth,const unsigned char& currentColor,int alpha,int beta,Board* PlayingBoard,bool drawProgress,unsigned char depthCounter)
{
    alphaBetaCalls++;
    int positionTested=0;
    int val;
    if ((depth < computedDepth)&&(!drawProgress))
        return value;
    if (depth <= 0)
    {
        evaluateCalls++;
        return PlayingBoard->evaluate(currentColor);
    }

    generateMoves(PlayingBoard);
    if(NextMoveList->m_moveNodeList.size()==0)
    {
        value=-20000;
        return value;
    }
#if ENABLE_SEARCH_ORDERING
    std::sort(NextMoveList->m_moveNodeList.begin(),NextMoveList->m_moveNodeList.end());
#endif
    if((drawProgress)&&(depth==1))
    {
        std::cout << "\nPossible moves : " ;
        for(std::vector<MoveTreeNode*>::iterator iter = NextMoveList->m_moveNodeList.begin();iter!=NextMoveList->m_moveNodeList.end();++iter)
        {
            std::cout << char((*iter)->m_move.origin.x+97)<<int((*iter)->m_move.origin.y+1)<< "-" << char((*iter)->m_move.destination.x+97)<<int((*iter)->m_move.destination.y+1) << " ; ";
        }
    }
    positionsGenerated+=NextMoveList->m_moveNodeList.size();


    std::vector<MoveTreeNode*>::iterator iter = NextMoveList->m_moveNodeList.begin();
    while (iter != NextMoveList->m_moveNodeList.end())
    {
        if(drawProgress)
        {
            positionTested++;
            std::cout << positionTested*100/NextMoveList->m_moveNodeList.size() << "%..";
        }
        positionsEvaluated++;
        unsigned char undo_OriginData=PlayingBoard->m_board_Data[(*iter)->m_move.origin.x][(*iter)->m_move.origin.y];
        unsigned char undo_DestinationData=PlayingBoard->m_board_Data[(*iter)->m_move.destination.x][(*iter)->m_move.destination.y];
        if (!PlayingBoard->makeMove(*iter))
            val=-20000;
        else
        {
            val = -(*iter)->alphaBeta(depth - 1,(*iter)->PlayerSide,-beta,-alpha,PlayingBoard,false,depthCounter+1);
            bool playerWaiting;
            pthread_mutex_lock(&playerPlayedMutex);
            playerWaiting=playerPlayed;
            pthread_mutex_unlock(&playerPlayedMutex);
            if(playerWaiting)
            {
                PlayingBoard->unMakeMove(*iter,undo_OriginData,undo_DestinationData);
                return 0;
            }
        }

        if (val >= beta)
        {
            value=beta;
            computedDepth=depth;
            PlayingBoard->unMakeMove(*iter,undo_OriginData,undo_DestinationData);
            //////////////////////////////////////////////////////////////////////////
            // TRY THE SORTING SYSTEM (FOR ITERATIVE DEEPENING)
            //////////////////////////////////////////////////////////////////////////
#if ENABLE_SEARCH_ORDERING
            std::sort(NextMoveList->m_moveNodeList.begin(),NextMoveList->m_moveNodeList.end());
#endif
            //////////////////////////////////////////////////////////////////////////
            if((!drawProgress)&& (depthCounter>DEPTHMEMORY))
            {
                std::vector<MoveTreeNode*>::iterator iter2 = NextMoveList->m_moveNodeList.begin();
                if(iter!=NextMoveList->m_moveNodeList.end())
                {
                    iter2++;
                    for(unsigned int i=1;i<NextMoveList->m_moveNodeList.size();++i)
                        delete NextMoveList->m_moveNodeList[i];
                    NextMoveList->m_moveNodeList.erase(iter2,NextMoveList->m_moveNodeList.end());
                }
            }
            return beta;
        }
        if (val > alpha)
            alpha = val;
        PlayingBoard->unMakeMove(*iter,undo_OriginData,undo_DestinationData);
        ++iter;
    }
    value = alpha;
    computedDepth=depth;
    //////////////////////////////////////////////////////////////////////////
    // TRY THE SORTING SYSTEM (FOR ITERATIVE DEEPENING)
    //////////////////////////////////////////////////////////////////////////
#if ENABLE_SEARCH_ORDERING
    std::sort(NextMoveList->m_moveNodeList.begin(),NextMoveList->m_moveNodeList.end());
#endif
    //////////////////////////////////////////////////////////////////////////
    if((!drawProgress) && (depthCounter>DEPTHMEMORY))
    {
        std::vector<MoveTreeNode*>::iterator iter2 = NextMoveList->m_moveNodeList.begin();
        if(iter!=NextMoveList->m_moveNodeList.end())
        {
            iter2++;
            for(unsigned int i=1;i<NextMoveList->m_moveNodeList.size();++i)
                delete NextMoveList->m_moveNodeList[i];
            NextMoveList->m_moveNodeList.erase(iter2,NextMoveList->m_moveNodeList.end());
        }
    }
    return alpha;
}
