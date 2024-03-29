#include "Board.h"
#include <iostream>
#include <assert.h>
#include "MoveTreeNode.h"
#include <windows.h>

Board::Board(void)
{


}


Board::~Board(void)
{
}

void Board::setupBoard()
{
    return debugSetup();
    int i,j;
	for (i=0;i<BOARD_SIZE;i++)
	{
		for (j=0;j<BOARD_SIZE;j++)
		{
			m_board_Data[i][j]=0;
		}
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		m_board_Data[i][0]|=WHITE;
		m_board_Data[i][1]|=WHITE;
		m_board_Data[i][1]|=PAWN_MASK;
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		m_board_Data[i][7]|=BLACK;
		m_board_Data[i][6]|=BLACK;
		m_board_Data[i][6]|=PAWN_MASK;
	}

	m_board_Data[0][7]|=ROOK_MASK;
	m_board_Data[0][0]|=ROOK_MASK;
	m_board_Data[7][7]|=ROOK_MASK;
	m_board_Data[7][0]|=ROOK_MASK;
    m_board_Data[1][7]|=KNIGHT_MASK;
	m_board_Data[1][0]|=KNIGHT_MASK;
	m_board_Data[6][7]|=KNIGHT_MASK;
	m_board_Data[6][0]|=KNIGHT_MASK;
	m_board_Data[2][7]|=BISHOP_MASK;
	m_board_Data[2][0]|=BISHOP_MASK;
	m_board_Data[5][7]|=BISHOP_MASK;
	m_board_Data[5][0]|=BISHOP_MASK;
	m_board_Data[3][7]|=QUEEN_MASK;
	m_board_Data[3][0]|=QUEEN_MASK;
	m_board_Data[4][7]|=KING_MASK;
	m_board_Data[4][0]|=KING_MASK;
}

void Board::debugSetup()
{
	int i,j;
	for (i=0;i<BOARD_SIZE;i++)
	{
		for (j=0;j<BOARD_SIZE;j++)
		{
			m_board_Data[i][j]=0;
		}
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		m_board_Data[i][0]|=WHITE;
		m_board_Data[i][1]|=WHITE;
		m_board_Data[i][1]|=PAWN_MASK;
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		m_board_Data[i][7]|=BLACK;
		m_board_Data[i][6]|=BLACK;
		m_board_Data[i][6]|=PAWN_MASK;
	}

	m_board_Data[0][7]|=ROOK_MASK;
	m_board_Data[0][0]|=ROOK_MASK;
	m_board_Data[7][7]|=ROOK_MASK;
	m_board_Data[7][0]|=ROOK_MASK;
    m_board_Data[1][7]|=KNIGHT_MASK;
	m_board_Data[1][0]|=KNIGHT_MASK;
	m_board_Data[6][7]|=KNIGHT_MASK;
	m_board_Data[6][0]|=KNIGHT_MASK;
	m_board_Data[2][7]|=BISHOP_MASK;
	m_board_Data[2][0]|=BISHOP_MASK;
	m_board_Data[5][7]|=BISHOP_MASK;
	m_board_Data[5][0]|=BISHOP_MASK;
	m_board_Data[3][7]|=QUEEN_MASK;
	m_board_Data[3][0]|=QUEEN_MASK;
	m_board_Data[4][7]|=KING_MASK;
	m_board_Data[4][0]|=KING_MASK;

    m_board_Data[1][0]=0;
    m_board_Data[5][0]=0;
    m_board_Data[6][0]=0;
    m_board_Data[4][1]=0;
    m_board_Data[0][6]=0;
    m_board_Data[1][6]=0;
    m_board_Data[1][7]=0;
    m_board_Data[4][6]=0;
    m_board_Data[5][7]=0;
    m_board_Data[0][5]=BOARD_B_PAWN;
    m_board_Data[2][4]=BOARD_B_PAWN;
    m_board_Data[1][3]=BOARD_W_KNIGHT;
    m_board_Data[3][5]=BOARD_B_PAWN;
    m_board_Data[4][3]=BOARD_W_PAWN;
    m_board_Data[4][4]=BOARD_B_PAWN;
    m_board_Data[5][2]=BOARD_W_KNIGHT;
}


void Board::drawBoard()
{
    drawBoard(std::cout);
}

void Board::drawBoard(std::ostream& stream)
{
	int i, j;

    stream << "\n"<<name<<"\n\n";
	for (j=BOARD_SIZE-1;j>=0;j--)
	{
		stream << j+1 << " ";
		for (i=0;i<BOARD_SIZE;i++)
		{
			if (m_board_Data[i][j]==BOARD_W_PAWN)
				stream << "P";
			else if (m_board_Data[i][j]==BOARD_W_KNIGHT)
				stream << "N";
			else if (m_board_Data[i][j]==BOARD_W_BISHOP)
				stream << "B";
			else if (m_board_Data[i][j]==BOARD_W_ROOK)
				stream << "R";
			else if (m_board_Data[i][j]==BOARD_W_QUEEN)
				stream << "Q";
			else if (m_board_Data[i][j]==BOARD_W_KING)
				stream << "K";
			else if (m_board_Data[i][j]==BOARD_B_PAWN)
				stream << "p";
			else if (m_board_Data[i][j]==BOARD_B_KNIGHT)
				stream << "n";
			else if (m_board_Data[i][j]==BOARD_B_BISHOP)
				stream << "b";
			else if (m_board_Data[i][j]==BOARD_B_ROOK)
				stream << "r";
			else if (m_board_Data[i][j]==BOARD_B_QUEEN)
				stream << "q";
			else if (m_board_Data[i][j]==BOARD_B_KING)
				stream << "k";
			else
			{
                stream << ".";
				/*if((i+j)%2==0)
				{
					stream << ".";
				}
				else
				{
					stream << ".";
				}*/
			}
		}
		stream << "\n";
	}
    stream << "\n  ";
	for (i=0;i<BOARD_SIZE;i++)
		stream << char(i+97);
	stream << "\n\n";
//    Sleep(1000);
}


int Board::evaluate( const unsigned char colorValue )
{
    //drawBoard();
	int i,j,val=0;
    unsigned char PlayerBishopCount=0,OpponentBishopCount=0,PlayerRookCount=0,OpponentRookCount=0;
	for (i=0;i<BOARD_SIZE;i++)
	{
        char PlayerPawnChain=-1,OpponentPawnChain=-1;
        for (j=BOARD_SIZE-1;j>=0;j--)
        {
			if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&PAWN_MASK))
            {
                PlayerPawnChain++;
                val+=100;
            }
			else if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&KNIGHT_MASK))
				val+=350;
			else if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&BISHOP_MASK))
            {
                PlayerBishopCount++;
				val+=350;
            }
			else if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&ROOK_MASK))
            {
                PlayerRookCount++;
                val+=500;
            }
			else if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&QUEEN_MASK))
				val+=950;
			else if ((m_board_Data[i][j]&colorValue)&&(m_board_Data[i][j]&KING_MASK))
				val+=10000;
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&PAWN_MASK))
            {
                OpponentPawnChain++;
				val-=100;
            }
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&KNIGHT_MASK))
				val-=350;
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&BISHOP_MASK))
            {
                OpponentBishopCount++;
                val-=350;
            }
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&ROOK_MASK))
            {
                OpponentRookCount++;
                val-=500;
            }
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&QUEEN_MASK))
				val-=950;
			else if (((~m_board_Data[i][j]&COLOR_MASK)==colorValue)&&(m_board_Data[i][j]&KING_MASK))
				val-=10000;
		}
        if(PlayerPawnChain>=1)
            val-=30;
        if(PlayerPawnChain>=2)
            val-=70*(PlayerPawnChain-1);
        if(OpponentPawnChain>=1)
            val+=30;
        if(OpponentPawnChain>=2)
            val+=70*(PlayerPawnChain-1);
	}
    if(PlayerBishopCount=2)
        val+=50;
    if(PlayerRookCount=2)
        val+=75;
    if(OpponentBishopCount=2)
        val-=50;
    if(OpponentRookCount=2)
        val-=75;
	for (j=2;j<6;++j)
	{
		if(m_board_Data[2][j]&colorValue)
			val+=1;
		if((~m_board_Data[2][j]&COLOR_MASK)==colorValue)
			val-=1;
		if(m_board_Data[3][j]&colorValue)
			val+=2;
		if((~m_board_Data[3][j]&COLOR_MASK)==colorValue)
			val-=2;
		if(m_board_Data[5][j]&colorValue)
			val+=1;
		if((~m_board_Data[5][j]&COLOR_MASK)==colorValue)
			val-=1;
		if(m_board_Data[4][j]&colorValue)
			val+=2;
		if((~m_board_Data[4][j]&COLOR_MASK)==colorValue)
			val-=2;
	}
    //std::cout << "evaluate for " << ((colorValue==unsigned char(1))?"WHITE ":"BLACK ") << val<<"\n";
	return val;
}

bool Board::makeMove( MoveTreeNode* moveNode , bool forceDisplay)
{
	unsigned char playColor = m_board_Data[moveNode->m_move.origin.x][moveNode->m_move.origin.y]&COLOR_MASK;
    m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]=m_board_Data[moveNode->m_move.origin.x][moveNode->m_move.origin.y];
    if ((m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]==BOARD_W_PAWN)&&(moveNode->m_move.destination.y==BOARD_SIZE-1))
    {
        m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]=BOARD_W_QUEEN;
    }
    else if ((m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]==BOARD_B_PAWN)&&(moveNode->m_move.destination.y==0))
    {
        m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]=BOARD_B_QUEEN;
    }
	m_board_Data[moveNode->m_move.origin.x][moveNode->m_move.origin.y]=0;
	isWhiteCheck=isCheck(WHITE,forceDisplay && (playColor==WHITE));
	isBlackCheck=isCheck(BLACK,forceDisplay && (playColor==BLACK));
	bool valid;
	if(playColor==WHITE)
		valid=!isWhiteCheck;
	else
		valid =!isBlackCheck;
	return valid;
}

void Board::unMakeMove( MoveTreeNode* moveNode, const unsigned char undo_OriginData,const unsigned char undo_DestinationData)
{
    m_board_Data[moveNode->m_move.origin.x][moveNode->m_move.origin.y]=undo_OriginData;
    m_board_Data[moveNode->m_move.destination.x][moveNode->m_move.destination.y]=undo_DestinationData;
}

bool Board::isCheck( const unsigned char colorValue, bool forceDisplay/*=false*/ )
{   
	bool debugDisplay =forceDisplay;
	bool returnValue=false;
	Position kingPos;
    unsigned char kingValueToSearch;
    unsigned char enemyQueen=QUEEN_MASK;
    unsigned char enemyRook=ROOK_MASK;
    unsigned char enemyKnight=KNIGHT_MASK;
    unsigned char enemyBishop=BISHOP_MASK;
    unsigned char enemyPawn=PAWN_MASK;
    unsigned char enemyKing=KING_MASK;
    enemyQueen |=(~colorValue&COLOR_MASK);
    enemyRook |=(~colorValue&COLOR_MASK);
    enemyKnight |=(~colorValue&COLOR_MASK);
    enemyBishop |=(~colorValue&COLOR_MASK);
    enemyPawn |=(~colorValue&COLOR_MASK);
    enemyKing |=(~colorValue&COLOR_MASK);
    kingValueToSearch = KING_MASK|colorValue;
	int x,y;
	x=BOARD_SIZE;
	bool found=false;
	while ((x>0)&&(!found))
	{
		--x;
		y=BOARD_SIZE;
		while ((y>0)&&(!found))
		{
			--y;
			if (m_board_Data[x][y]==kingValueToSearch)
			{
				kingPos.x=x;
				kingPos.y=y;
				found=true;
			}
		}
	}
	if(!found)
	{
		return true;
	}
	int x2=kingPos.x;
	int y2=kingPos.y;
	found=false;
	while ((x2>0)&&(!found))
	{
		--x2;
		if(m_board_Data[x2][y2]!=0)
		{
        	if((m_board_Data[x2][y2]==enemyRook)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
		}
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((x2<BOARD_SIZE-1)&&(!found))
	{
		++x2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyRook)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2>0)&&(!found))
	{
		--y2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyRook)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2<BOARD_SIZE-1)&&(!found))
	{
		++y2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyRook)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2>0)&&(x2>0)&&(!found))
	{
		--y2;
		--x2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyBishop)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2<BOARD_SIZE-1)&&(x2>0)&&(!found))
	{
		++y2;
		--x2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyBishop)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2>0)&&(x2<BOARD_SIZE-1)&&(!found))
	{
		--y2;
		++x2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyBishop)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x;
	y2=kingPos.y;
	found=false;
	while ((y2<BOARD_SIZE-1)&&(x2<BOARD_SIZE-1)&&(!found))
	{
		++y2;
		++x2;
        if(m_board_Data[x2][y2]!=0)
        {
            if((m_board_Data[x2][y2]==enemyBishop)||(m_board_Data[x2][y2]==enemyQueen))
            {
                return true;
            }
            else
            {
                found=true;
            }
        }
	}
	x2=kingPos.x-1;
	y2=kingPos.y-2;
	if((y2>=0)&&(x2>=0))
	{
		if(m_board_Data[x2][y2]==enemyKnight)
		{
			return true;
		}
	}
	x2=kingPos.x-2;
	y2=kingPos.y-1;
	if((y2>=0)&&(x2>=0))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x-1;
	y2=kingPos.y+2;
	if((y2<BOARD_SIZE)&&(x2>=0))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x-2;
	y2=kingPos.y+1;
	if((y2<BOARD_SIZE)&&(x2>=0))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x+1;
	y2=kingPos.y-2;
	if((y2>=0)&&(x2<BOARD_SIZE))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x+2;
	y2=kingPos.y-1;
	if((y2>=0)&&(x2<BOARD_SIZE))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x+1;
	y2=kingPos.y+2;
	if((y2<BOARD_SIZE)&&(x2<BOARD_SIZE))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
	x2=kingPos.x+2;
	y2=kingPos.y+1;
	if((y2<BOARD_SIZE)&&(x2<BOARD_SIZE))
	{
        if(m_board_Data[x2][y2]==enemyKnight)
        {
            return true;
        }
	}
    if(colorValue==WHITE)
    {
        y2=kingPos.y+1;
    }
    else
    {
        y2=kingPos.y-1;
    }
    x2=kingPos.x+1;
    if((y2<BOARD_SIZE)&&(y2>=0)&&(x2<BOARD_SIZE))
    {
        if(m_board_Data[x2][y2]==enemyPawn)
        {
            return true;
        }
    }
    x2=kingPos.x-1;
    if((y2<BOARD_SIZE)&&(y2>=0)&&(x2>=0)&&(x2<BOARD_SIZE))
    {
        if(m_board_Data[x2][y2]==enemyPawn)
        {
            return true;
        }
    }
    
    for(x2=-1;x2<2;++x2)
    {
        for(y2=-1;y2<2;++y2)
        {
            int x3=x2+kingPos.x;
            int y3=y2+kingPos.y;
            if((y3<BOARD_SIZE)&&(y3>=0)&&(x3>=0)&&(x3<BOARD_SIZE))
            {
                if(m_board_Data[x3][y3]==enemyKing)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
