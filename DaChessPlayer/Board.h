#pragma once

#include "constants.h"
#include "Position.h"
#include <fstream>
#include <string>

class MoveTreeNode;

class Board
{
public:
	Board(void);
	~Board(void);
    unsigned char m_board_Data[BOARD_SIZE][BOARD_SIZE];
    //char m_board_piece[BOARD_SIZE][BOARD_SIZE];
    std::string name;
    bool canWhite_ShortCastle;
    bool canWhite_LongCastle;
    bool canBlack_ShortCastle;
    bool canBlack_LongCastle;
    bool isWhiteCheck;
    bool isBlackCheck;
    void drawBoard();
	void drawBoard(std::ostream& stream);
    void setupBoard();
	void debugSetup();
    int evaluate(const unsigned char colorValue);
    bool makeMove(MoveTreeNode* moveNode, bool forceDisplay=false);
    void unMakeMove( MoveTreeNode* moveNode,const unsigned char undo_OriginData,const unsigned char undo_DestinationData);
    bool isCheck(const unsigned char colorValue, bool forceDisplay=false);
};

