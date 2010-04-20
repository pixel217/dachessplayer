// DaChessPlayer.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include "MoveTreeNodeList.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t ReflectionStructureMutex = PTHREAD_MUTEX_INITIALIZER;;
MoveTreeNode* ReflectionStructure;

pthread_mutex_t pleasePlayMutex = PTHREAD_MUTEX_INITIALIZER;;
bool pleasePlay;

pthread_mutex_t playerPlayedMutex = PTHREAD_MUTEX_INITIALIZER;;
bool playerPlayed;

int evaluateCalls;
int alphaBetaCalls;
int positionsGenerated;
int positionsEvaluated;

sem_t iPlayedSemaphore;

sem_t playerPlayedSemaphore;

Board CurrentBoard;
Board ThinkingBoard;
MoveTreeNode player;
bool gameEnded;

int depthThought;
bool ComputerPlaysWhite;
pthread_t thinkingThread;

void *thinkChessFunction(void* ptr)
{
    MoveTreeNode * lastBestMove = new MoveTreeNode();
    while(!gameEnded)
    {
        pthread_mutex_lock(&ReflectionStructureMutex);
        int best;
        if(depthThought<MAXDEPTH)
        {
#if ENABLE_ID
            depthThought++;
#else
            depthThought=MINDEPTH;
#endif
            std::cout << "thinking to depth : " << depthThought<<": ..";
			best = ReflectionStructure->alphaBeta(depthThought,ReflectionStructure->PlayerSide,-9999999,9999999,&ThinkingBoard,true);
            std::cout << "Done"<<std::endl;
        }
        else
        {
            std::cout << "Waiting for player"<<std::endl;
            bool playerWaiting;
            do 
            {
                pthread_mutex_lock(&playerPlayedMutex);
                playerWaiting=playerPlayed;
                pthread_mutex_unlock(&playerPlayedMutex);
            } while (!playerWaiting);
        }
        bool playerWaiting;
        pthread_mutex_lock(&playerPlayedMutex);
        playerWaiting=playerPlayed;
        pthread_mutex_unlock(&playerPlayedMutex);
        if(playerWaiting)
        {
            pthread_mutex_unlock(&ReflectionStructureMutex);
            sem_wait(&playerPlayedSemaphore);            
            pthread_mutex_lock(&ReflectionStructureMutex);
            pthread_mutex_lock(&playerPlayedMutex);
            playerPlayed=false;
            pthread_mutex_unlock(&playerPlayedMutex);
        }
        else
        {
            int localBest=90000;
            std::vector<MoveTreeNode*>::iterator bestMove=ReflectionStructure->NextMoveList->m_moveNodeList.end();
            for(std::vector<MoveTreeNode*>::iterator iter = ReflectionStructure->NextMoveList->m_moveNodeList.begin();iter != ReflectionStructure->NextMoveList->m_moveNodeList.end();++iter)
            {
                
                if(((*iter)->value)<localBest)
                {
                    bestMove=iter;
                    localBest=((*iter)->value);
                }
            }
            if(bestMove==ReflectionStructure->NextMoveList->m_moveNodeList.end())
            {
                if(ComputerPlaysWhite && CurrentBoard.isBlackCheck)
                {
                    std::cout << "You are Checkmated\n";
                }
                else if(ComputerPlaysWhite && CurrentBoard.isWhiteCheck)
                {
                    std::cout << "I am Checkmated\n";
                }
                else if(!ComputerPlaysWhite && CurrentBoard.isWhiteCheck)
                {
                    std::cout << "You are Checkmated\n";
                }
                else if(!ComputerPlaysWhite && CurrentBoard.isBlackCheck)
                {
                    std::cout << "I am Checkmated\n";
                }
                else
                {
                    std::cout <<"WTF!"<<std::endl;
                    DebugBreak();
                }
                exit(0);
            }
            lastBestMove->m_move=(*bestMove)->m_move;
            bool playNow;
            pthread_mutex_lock(&pleasePlayMutex);
            playNow=pleasePlay;
            pthread_mutex_unlock(&pleasePlayMutex);
            if(playNow && (depthThought>=MINDEPTH))
            {
                int actualBest=90000;
                std::vector<MoveTreeNode*>::iterator bestMove=ReflectionStructure->NextMoveList->m_moveNodeList.end();
                for(std::vector<MoveTreeNode*>::iterator iter = ReflectionStructure->NextMoveList->m_moveNodeList.begin();iter != ReflectionStructure->NextMoveList->m_moveNodeList.end();++iter)
                {
                    if(((*iter)->value)<actualBest)
                    {
                        bestMove=iter;
                        actualBest=((*iter)->value);
                    }
                }
                if(bestMove==ReflectionStructure->NextMoveList->m_moveNodeList.end())
                {
                    std::cout <<"boum!"<<std::endl;
                    exit(0);
                }
                if(localBest >=20000)
                {
                    std::cout << "\nMove played : " << char((*bestMove)->m_move.origin.x+97)<<int((*bestMove)->m_move.origin.y+1)<< "-" << char((*bestMove)->m_move.destination.x+97)<<int((*bestMove)->m_move.destination.y+1) << "\n";
                    std::cout << "Checkmate!\n";
                    exit(0);
                }
                MoveTreeNode* NextReflectionStructure = *bestMove;
                std::cout << "\nMove played : " << char((*bestMove)->m_move.origin.x+97)<<int((*bestMove)->m_move.origin.y+1)<< "-" << char((*bestMove)->m_move.destination.x+97)<<int((*bestMove)->m_move.destination.y+1) << "\n";
                CurrentBoard.makeMove(*bestMove);
                ThinkingBoard.makeMove(*bestMove);
                if(ComputerPlaysWhite && CurrentBoard.isBlackCheck)
                {
                    std::cout << "\n\nCHECK!\n\n";
                }
                ReflectionStructure->NextMoveList->DetachMove(bestMove);
                delete ReflectionStructure;
                ReflectionStructure=NextReflectionStructure;
                depthThought--;
                pthread_mutex_lock(&pleasePlayMutex);
                pleasePlay=false;
                pthread_mutex_unlock(&pleasePlayMutex);
                sem_post(&iPlayedSemaphore);
                Sleep(150);
				for(std::vector<MoveTreeNode*>::iterator iter = ReflectionStructure->NextMoveList->m_moveNodeList.begin();iter!=ReflectionStructure->NextMoveList->m_moveNodeList.end();++iter)
				{
					std::cout << char((*iter)->m_move.origin.x+97)<<int((*iter)->m_move.origin.y+1)<< "-" << char((*iter)->m_move.destination.x+97)<<int((*iter)->m_move.destination.y+1) << " ; ";
				}
                Sleep(20);
            }
        }
        pthread_mutex_unlock(&ReflectionStructureMutex);
    }
}


int main(int argc, char* argv[])
{
    evaluateCalls       =0;
    alphaBetaCalls      =0;
    positionsGenerated  =0;
    depthThought=0;
    sem_init(&iPlayedSemaphore,0,0);
    sem_init(&playerPlayedSemaphore,0,0);
    gameEnded=false;
    playerPlayed=false;
    pthread_mutex_lock(&pleasePlayMutex);
    pleasePlay=false;
    pthread_mutex_unlock(&pleasePlayMutex);
    pthread_mutex_lock(&ReflectionStructureMutex);
    ReflectionStructure = new MoveTreeNode();
    ReflectionStructure->PlayerSide=WHITE;
    pthread_mutex_unlock(&ReflectionStructureMutex);
    CurrentBoard.name="Current Board";
    ThinkingBoard.name="Thinking Board";
    CurrentBoard.setupBoard();
    ThinkingBoard.setupBoard();
    int iret1=pthread_create(&thinkingThread,NULL,thinkChessFunction,NULL);
    //CurrentBoard.drawBoard();
    char c;
    for(int turns=0;turns<50;++turns)
    {
        CurrentBoard.drawBoard();
        pthread_mutex_lock(&pleasePlayMutex);
        pleasePlay=true;
        pthread_mutex_unlock(&pleasePlayMutex);
        //ReflectionStructure->alphaBeta2(5,WHITE,&CurrentBoard,ReflectionStructure);
        sem_wait(&iPlayedSemaphore);
        CurrentBoard.drawBoard();
        //		Sleep(1000);
        //ReflectionStructure->alphaBeta2(3,BLACK,&CurrentBoard,ReflectionStructure);
        printf("start column: ");
        std::cin >> c;
        player.m_move.origin.x=c-97;
        printf("start row: ");
        std::cin >> c;
        player.m_move.origin.y=c-49;
        printf("end column: ");
        std::cin >> c;
        player.m_move.destination.x=c-97;
        printf("end row: ");
        std::cin >> c;
        player.m_move.destination.y=c-49;
        pthread_mutex_lock(&playerPlayedMutex);
        playerPlayed=true;
        pthread_mutex_unlock(&playerPlayedMutex);
        //CurrentBoard.makeMove(&player);
        pthread_mutex_lock(&ReflectionStructureMutex);
        std::vector<MoveTreeNode*>::iterator moveToDo;
        for(std::vector<MoveTreeNode*>::iterator iter = ReflectionStructure->NextMoveList->m_moveNodeList.begin();iter != ReflectionStructure->NextMoveList->m_moveNodeList.end();++iter)
        {
            if((*iter)->m_move==player.m_move)
                moveToDo=iter;
        }
        MoveTreeNode* NextReflectionStructure = *moveToDo;
        CurrentBoard.makeMove(*moveToDo);
        ThinkingBoard.makeMove(*moveToDo);
        ReflectionStructure->NextMoveList->DetachMove(moveToDo);
        delete ReflectionStructure;
        ReflectionStructure=NextReflectionStructure;
        depthThought=0;
        pthread_mutex_unlock(&ReflectionStructureMutex);
        sem_post(&playerPlayedSemaphore);
        //CurrentBoard.drawBoard();
        //		Sleep(1000);
    }
    return 0;
}

