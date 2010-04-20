//////////////////////////////////////////////////////////////////////////
// TODO
// - implement the "Castle" move
// - implement pondering
// - implement transposition tables
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "constants.h"

struct position
{
    unsigned char x;
    unsigned char y;
};

struct movestruct
{
    position origin;
    position destination;
    movestruct* next;
};

typedef struct movestruct move;

move* player=new(move);

// VARS

int piece[BOARD_SIZE][BOARD_SIZE];
int color[BOARD_SIZE][BOARD_SIZE];
int positionsTested;
bool wCheck, bCheck;

bool isCheck(int);

move* generateLegalMoves(int, move**);

void makeMove(move*);

void setUpBoard();

void addMove(position,position, move**, move***);

void displayMoves(move*);

void updateCheck();

void isBlackCheck(position);

void isWhiteCheck(position);

int evaluate(int);

int countElements(move*);

int minBOARD_SIZE(int,int);

int alphaBeta(int,int,int,int);

int alphaBeta2(int,int);

void drawBoard()
{
	int i, j;

	for (j=BOARD_SIZE-1;j>=0;j--)
	{
		printf("%d ",j+1);
		for (i=0;i<BOARD_SIZE;i++)
		{
			if ((color[i][j]==WHITE)&&(piece[i][j]==PAWN))
				printf("P");
			else if ((color[i][j]==WHITE)&&(piece[i][j]==KNIGHT))
				printf("N");
			else if ((color[i][j]==WHITE)&&(piece[i][j]==BISHOP))
				printf("B");
			else if ((color[i][j]==WHITE)&&(piece[i][j]==ROOK))
				printf("R");
			else if ((color[i][j]==WHITE)&&(piece[i][j]==QUEEN))
				printf("Q");
			else if ((color[i][j]==WHITE)&&(piece[i][j]==KING))
				printf("K");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==PAWN))
				printf("p");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==KNIGHT))
				printf("n");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==BISHOP))
				printf("b");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==ROOK))
				printf("r");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==QUEEN))
				printf("q");
			else if ((color[i][j]==BLACK)&&(piece[i][j]==KING))
				printf("k");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n  ");
	for (i=0;i<BOARD_SIZE;i++)
		printf("%c",i+97);
	printf("\n");

}


move* generateLegalMoves(int currentColor, move** captures)
{
	move* movesToReturn=NULL;
	if (*captures != NULL)
	{
		printf("captures non nulles!!!\n");
		exit(0);
	}
	position testPos,possibleNewPos;
	for (testPos.x = 0; testPos.x < BOARD_SIZE; testPos.x++)
	{
		for (testPos.y = 0; testPos.y < BOARD_SIZE; testPos.y++)
		{
			if (color[testPos.x][testPos.y] == currentColor)
			{
				if (piece[testPos.x][testPos.y] == PAWN)
				{
					possibleNewPos.x=testPos.x;
					possibleNewPos.y=testPos.y+currentColor;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x+1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x-1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					if (((testPos.y==1)&&(currentColor==WHITE))||
						((testPos.y==BOARD_SIZE-2)&&(currentColor==BLACK)))
					{
						possibleNewPos.x=testPos.x;
						possibleNewPos.y=testPos.y+(currentColor*2);
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					}
				}
				if (piece[testPos.x][testPos.y] == KNIGHT)
				{
					possibleNewPos.y=testPos.y+2;
					possibleNewPos.x=testPos.x+1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x-1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.y=testPos.y-2;
					possibleNewPos.x=testPos.x+1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x-1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x-2;
					possibleNewPos.y=testPos.y+1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.y=testPos.y-1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.x=testPos.x+2;
					possibleNewPos.y=testPos.y-1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					possibleNewPos.y=testPos.y+1;
					addMove(testPos,possibleNewPos,&movesToReturn, &captures);
				}
				if (piece[testPos.x][testPos.y] == BISHOP)
				{
					for (int i= -1*BOARD_SIZE+1;i<BOARD_SIZE;i++)
					{
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x-i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					}
				}
				if (piece[testPos.x][testPos.y] == ROOK)
				{
					for (int i= -1*BOARD_SIZE+1;i<BOARD_SIZE;i++)
					{
						possibleNewPos.x=testPos.x;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					}
				}
				if (piece[testPos.x][testPos.y] == QUEEN)
				{
					for (int i= -1*BOARD_SIZE+1;i<BOARD_SIZE;i++)
					{
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x-i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					}
				}
				if (piece[testPos.x][testPos.y] == KING)
				{
					for (int i= -1;i<2;i++)
					{
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x-i;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x;
						possibleNewPos.y=testPos.y+i;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
						possibleNewPos.x=testPos.x+i;
						possibleNewPos.y=testPos.y;
						addMove(testPos,possibleNewPos,&movesToReturn, &captures);
					}
				}
			}
		}
	}
	return movesToReturn;
}

void addMove(position origin,position destination, move** movesToReturn, move*** captures)
{
	//la case est hors plateau
	if ((destination.x<0)||(destination.x>(BOARD_SIZE-1))||(destination.y<0)||(destination.y>(BOARD_SIZE-1)))
		return;
	//la case est occupée par une piece de meme couleur
	if (color[destination.x][destination.y]==color[origin.x][origin.y])
		return;
	//avancer le pion sur une case occupée
	if ((piece[origin.x][origin.y] == PAWN)&&(destination.x==origin.x)&&
		(((destination.y==origin.y-2)&&(piece[origin.x][origin.y-2]))||
		((destination.y==origin.y+2)&&(piece[origin.x][origin.y+2]))||
		((destination.y==origin.y+1)&&(piece[origin.x][origin.y+1]))||
		((destination.y==origin.y-1)&&(piece[origin.x][origin.y-1])))) 
		return;
	//avancer le pion de 2 alors qu'il y a une piece dans le chemin
	if ((piece[origin.x][origin.y] == PAWN)&&
		(((destination.y==origin.y-2)&&(piece[origin.x][origin.y-1]))||
		((destination.y==origin.y+2)&&(piece[origin.x][origin.y+1])))) 
		return;
	//prise du pion sans piece a prendre
	if ((piece[origin.x][origin.y] == PAWN)&&(color[origin.x][origin.y] != -color[destination.x][destination.y])&&(destination.x!=origin.x)&&
		((destination.y!=origin.y)&&(!piece[destination.x][destination.y])))
		return;
	
	//si c'est un fou ou une reine qui va vers le NE les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == BISHOP)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x>origin.x)&&(destination.y>origin.y))
	{
		for (int i=1;i<(destination.y-origin.y);i++)
			if (piece[origin.x+i][origin.y+i]) return;
	}
	//si c'est un fou ou une reine qui va vers le NW les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == BISHOP)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x<origin.x)&&(destination.y>origin.y))
	{
		for (int i=1;i<(destination.y-origin.y);i++)
			if (piece[origin.x-i][origin.y+i]) return;
	}
	//si c'est un fou ou une reine qui va vers le SE les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == BISHOP)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x>origin.x)&&(destination.y<origin.y))
	{
		for (int i=1;i<(origin.y-destination.y);i++)
			if (piece[origin.x+i][origin.y-i]) return;
	}
	//si c'est un fou ou une reine qui va vers le SW les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == BISHOP)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x<origin.x)&&(destination.y<origin.y))
	{
		for (int i=1;i<(origin.y-destination.y);i++)
			if (piece[origin.x-i][origin.y-i]) return;
	}
	//si c'est une tour ou une reine qui va vers le N les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == ROOK)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x==origin.x)&&(destination.y>origin.y))
	{
		for (int i=1;i<(destination.y-origin.y);i++)
			if (piece[origin.x][origin.y+i]) return;
	}
	//si c'est une tour ou une reine qui va vers le S les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == ROOK)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x==origin.x)&&(destination.y<origin.y))
	{
		for (int i=1;i<(origin.y-destination.y);i++)
			if (piece[origin.x][origin.y-i]) return;
	}
	//si c'est une tour ou une reine qui va vers le E les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == ROOK)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x>origin.x)&&(destination.y==origin.y))
	{
		for (int i=1;i<(destination.x-origin.x);i++)
			if (piece[origin.x+i][origin.y]) return;
	}
	//si c'est une tour ou une reine qui va vers le W les cases sur le chemin doivent etre libres
	if (((piece[origin.x][origin.y] == ROOK)||(piece[origin.x][origin.y] == QUEEN))&&
		(destination.x<origin.x)&&(destination.y==origin.y))
	{
		for (int i=1;i<(origin.x-destination.x);i++)
			if (piece[origin.x-i][origin.y]) return;
	}
	
	// si tout est bon, on ajoute le mouvement a la liste des mouvements si ce n'est pas une capture sinon a la liste des captures
	if (color[destination.x][destination.y]==0)
	{
		if (*movesToReturn != NULL)
		{
			move* newmove = new move();
			newmove->next = *movesToReturn;
			newmove->origin=origin;
			newmove->destination=destination;
			*movesToReturn = newmove;
		}
		else
		{
			*movesToReturn = new move();
			(*movesToReturn)->origin=origin;
			(*movesToReturn)->destination=destination;
			(*movesToReturn)->next=NULL;
		}
	}
	else
	{
		if (**captures != NULL)
		{
			move* newmove2 = new move();
			newmove2->next = **captures;
			newmove2->origin=origin;
			newmove2->destination=destination;
			**captures = newmove2;
		}
		else
		{
			**captures = new move();
			(**captures)->origin=origin;
			(**captures)->destination=destination;
			(**captures)->next=NULL;
		}
	}
	return;
}

void displayMoves(move* movesToDisplay)
{
	move* temp=movesToDisplay;
	int oldp,oldc;
	int n=1;
	
	while (temp != NULL)
	{
		oldc=color[temp->destination.x][temp->destination.y];
		oldp=piece[temp->destination.x][temp->destination.y];
		color[temp->destination.x][temp->destination.y]=color[temp->origin.x][temp->origin.y];
		piece[temp->destination.x][temp->destination.y]=piece[temp->origin.x][temp->origin.y];
		color[temp->origin.x][temp->origin.y]=0;
		piece[temp->origin.x][temp->origin.y]=0;
		printf("%d, evaluate: %d\n",n,evaluate(color[temp->destination.x][temp->destination.y]));
		n++;
		drawBoard();
		printf("\n");
		color[temp->origin.x][temp->origin.y]=color[temp->destination.x][temp->destination.y];
		piece[temp->origin.x][temp->origin.y]=piece[temp->destination.x][temp->destination.y];
		color[temp->destination.x][temp->destination.y]=oldc;
		piece[temp->destination.x][temp->destination.y]=oldp;
		temp=temp->next;
	}
	return;
}

void setUpBoard()
{
	int i,j;
	for (i=0;i<BOARD_SIZE;i++)
	{
		for (j=0;j<BOARD_SIZE;j++)
		{
			color[i][j]=0;
			piece[i][j]=0;
		}
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][0]=WHITE;
		color[i][1]=WHITE;
		piece[i][1]=PAWN;
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][7]=BLACK;
		color[i][6]=BLACK;
		piece[i][6]=PAWN;
	}
	
	piece[0][7]=ROOK;
	piece[0][0]=ROOK;
	piece[7][7]=ROOK;
	piece[7][0]=ROOK;
	piece[1][7]=KNIGHT;
	piece[1][0]=KNIGHT;
	piece[6][7]=KNIGHT;
	piece[6][0]=KNIGHT;
	piece[2][7]=BISHOP;
	piece[2][0]=BISHOP;
	piece[5][7]=BISHOP;
	piece[5][0]=BISHOP;
	piece[3][7]=QUEEN;
	piece[3][0]=QUEEN;
	piece[4][7]=KING;
	piece[4][0]=KING;
	
}

void setUpBoard2()
{
	int i,j;
	for (i=0;i<BOARD_SIZE;i++)
	{
		for (j=0;j<BOARD_SIZE;j++)
		{
			color[i][j]=0;
			piece[i][j]=0;
		}
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][0]=WHITE;
		color[i][1]=WHITE;
		piece[i][1]=PAWN;
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][7]=BLACK;
		color[i][6]=BLACK;
		piece[i][6]=PAWN;
	}
	
	piece[0][7]=ROOK;
	piece[0][0]=ROOK;
	piece[7][7]=ROOK;
	piece[7][0]=ROOK;
	piece[1][7]=KNIGHT;
	piece[1][0]=KNIGHT;
	piece[6][7]=KNIGHT;
	piece[6][0]=KNIGHT;
	piece[2][7]=BISHOP;
	piece[2][0]=BISHOP;
	piece[5][7]=BISHOP;
	piece[5][0]=BISHOP;
	piece[3][7]=QUEEN;
	piece[3][0]=QUEEN;
	piece[4][7]=KING;
	piece[4][0]=KING;

	piece[1][7]=0;
	color[1][7]=0;
	piece[2][6]=0;
	color[2][6]=0;
	piece[3][6]=0;
	color[3][6]=0;
	piece[4][6]=0;
	color[4][6]=0;

	piece[3][1]=0;
	color[3][1]=0;
	piece[5][0]=0;
	color[5][0]=0;
	piece[6][0]=0;
	color[6][0]=0;

	piece[3][2]=PAWN;
	color[3][2]=WHITE;
	piece[4][3]=PAWN;
	color[4][3]=WHITE;
	piece[5][2]=KNIGHT;
	color[5][2]=WHITE;
	piece[4][1]=BISHOP;

	piece[2][4]=PAWN;
	color[2][4]=BLACK;
	piece[3][4]=PAWN;
	color[3][4]=BLACK;
	piece[4][5]=PAWN;
	color[4][5]=BLACK;
	piece[2][5]=KNIGHT;
	color[2][5]=BLACK;
	
}

void setUpBoard3()
{
	int i,j;
	for (i=0;i<BOARD_SIZE;i++)
	{
		for (j=0;j<BOARD_SIZE;j++)
		{
			color[i][j]=0;
			piece[i][j]=0;
		}
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][0]=WHITE;
		color[i][1]=WHITE;
		piece[i][1]=PAWN;
	}
	for (i=0;i<BOARD_SIZE;i++)
	{
		color[i][4]=BLACK;
		color[i][3]=BLACK;
		piece[i][3]=PAWN;
	}
	
	piece[0][4]=ROOK;
	piece[0][0]=ROOK;
	piece[4][4]=ROOK;
	piece[4][0]=ROOK;
	piece[1][4]=KNIGHT;
	piece[1][0]=KNIGHT;
	piece[3][4]=KNIGHT;
	piece[3][0]=KNIGHT;
	piece[2][4]=KING;
	piece[2][0]=KING;

}



int main(int argc, char* argv[])
{
	int w;
	//winboard interfacing setbuf(stdout, NULL);
	// setbuf(stdin, NULL);
	setUpBoard();
	drawBoard();
	printf("\n");
	
	for(w=0;w<600;w++)
	{	
        char c;
		//minBOARD_SIZE(6,WHITE);
        drawBoard();
		printf("value of the board (WHITE): %d\n",evaluate(WHITE));
		printf("value of the board after the thinking of WHITE: %d\n",alphaBeta2(MAXDEPTH,WHITE));
		printf("best for WHITE:\n");

        /*printf("start column: ");
        std::cin >> c;
        player->origin.x=c-97;
        printf("start row: ");
        std::cin >> c;
        player->origin.y=c-49;
        printf("end column: ");
        std::cin >> c;
        player->destination.x=c-97;
        printf("end row: ");
        std::cin >> c;
        player->destination.y=c-49;
        player->next=NULL;
        makeMove(player);*/
        drawBoard();

        printf("\n");
		if (isCheck(BLACK))
			printf("CHECK!\n");

		printf("value of the board (BLACK): %d\n",evaluate(BLACK));
        printf("start column: ");
        std::cin >> c;
        player->origin.x=c-97;
        printf("start row: ");
        std::cin >> c;
        player->origin.y=c-49;
        printf("end column: ");
        std::cin >> c;
        player->destination.x=c-97;
        printf("end row: ");
        std::cin >> c;
        player->destination.y=c-49;
        player->next=NULL;
        makeMove(player);

//   		printf("value of the board after the thinking of BLACK: %d\n",alphaBeta2(5,BLACK));
//   		printf("best for BLACK:\n");
		
//		drawBoard();
        printf("\n");
		if (isCheck(WHITE))
			printf("CHECK!\n");
	}
	return 0;
}



int evaluate(int colorValue)
{
	int i,j,val=0;
	for (j=BOARD_SIZE-1;j>=0;j--)
	{
		for (i=0;i<BOARD_SIZE;i++)
		{
			if ((color[i][j]==colorValue)&&(piece[i][j]==PAWN))
				val+=100;
			else if ((color[i][j]==colorValue)&&(piece[i][j]==KNIGHT))
				val+=300;
			else if ((color[i][j]==colorValue)&&(piece[i][j]==BISHOP))
				val+=300;
			else if ((color[i][j]==colorValue)&&(piece[i][j]==ROOK))
				val+=700;
			else if ((color[i][j]==colorValue)&&(piece[i][j]==QUEEN))
				val+=900;
			else if ((color[i][j]==colorValue)&&(piece[i][j]==KING))
				val+=9999999;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==PAWN))
				val-=100;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==KNIGHT))
				val-=300;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==BISHOP))
				val-=300;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==ROOK))
				val-=700;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==QUEEN))
				val-=900;
			else if ((color[i][j]!=colorValue)&&(piece[i][j]==KING))
				val-=9999999;
		}
	}
	move *temp2,*captures=NULL;
	move *temp=generateLegalMoves(colorValue,&captures);
	val+= countElements(temp);
	val+= countElements(captures);
	while (captures != NULL)
	{
		temp2=captures;
		captures=captures->next;
        temp2->next = NULL;
        delete temp2;
	}
	while (temp != NULL)
	{
		temp2=temp;
		temp=temp->next;
        temp2->next = NULL;
        delete temp2;
	}
	temp=generateLegalMoves(-colorValue,&captures);
	val-= countElements(temp);
	val-= countElements(captures);
	while (captures != NULL)
	{
		temp2=captures;
		captures=captures->next;
        temp2->next = NULL;
        delete temp2;
	}
	while (temp != NULL)
	{
		temp2=temp;
		temp=temp->next;
        temp2->next = NULL;
        delete temp2;
	}
	return val;
}

/* WOULD NEED TO BE UPDATED
int minBOARD_SIZE(int depth,int currentColor)
{
    int val,best = -99999999;
	
    if (depth <= 0)
        return evaluate(currentColor);
	
	move* temp2,*temp=generateLegalMoves(currentColor);
	int oldp,oldc,oldp2,oldc2;
	
	while (temp != NULL)
	{
		oldc=color[temp->destination.x][temp->destination.y];
		oldp=piece[temp->destination.x][temp->destination.y];
		oldc2=color[temp->origin.x][temp->origin.y];
		oldp2=piece[temp->origin.x][temp->origin.y];
		makeMove(temp);
		color[temp->origin.x][temp->origin.y]=0;
		piece[temp->origin.x][temp->origin.y]=0;
        
		val = -minBOARD_SIZE(depth - 1,-currentColor);
		
		color[temp->destination.x][temp->destination.y]=oldc;
		piece[temp->destination.x][temp->destination.y]=oldp;
		color[temp->origin.x][temp->origin.y]=oldc2;
		piece[temp->origin.x][temp->origin.y]=oldp2;
        if (val > best)
		{
            best = val;
			temp2=temp;
		}
		temp=temp->next;
		
	}
	if (bestmoves != NULL)
	{
		move* last = bestmoves;
		bestmoves = new move();
		bestmoves->origin=temp2->origin;
		bestmoves->destination=temp2->destination;
		bestmoves->next=last;
		return best;
	}
	bestmoves = new move();
	bestmoves->origin=temp2->origin;
	bestmoves->destination=temp2->destination;
	bestmoves->next=NULL;
    return best;
}
*/

int alphaBeta(int depth,int currentColor,int alpha,int beta)
{
    int val;
	if (depth <= 0)
        return evaluate(currentColor);
	
	move *captures=NULL,*temp3,*temp2, *capt2;
	move *temp=generateLegalMoves(currentColor,&captures);
	int oldp,oldc,oldp2,oldc2;
	temp2=temp;
	capt2=captures;
	while (captures != NULL)
	{
		oldc=color[captures->destination.x][captures->destination.y];
		oldp=piece[captures->destination.x][captures->destination.y];
		oldc2=color[captures->origin.x][captures->origin.y];
		oldp2=piece[captures->origin.x][captures->origin.y];
		makeMove(captures);
        positionsTested++;
		if (isCheck(currentColor))
			val=-9999999;
			else
			val = -alphaBeta(depth - 1,-currentColor,-beta,-alpha);
		
		color[captures->destination.x][captures->destination.y]=oldc;
		piece[captures->destination.x][captures->destination.y]=oldp;
		color[captures->origin.x][captures->origin.y]=oldc2;
		piece[captures->origin.x][captures->origin.y]=oldp2;
        if (val >= beta)
		{
			while (capt2 != NULL)
			{
				temp3=capt2;
				capt2=capt2->next;
                temp3->next = NULL;
                delete temp3;
			}
			while (temp2 != NULL)
			{
				temp3=temp2;
				temp2=temp2->next;
                temp3->next = NULL;
                delete temp3;
			}
			return beta;
		}
	    if (val > alpha)
	        alpha = val;
		captures=captures->next;
	}
	while (capt2 != NULL)
	{
		temp3=capt2;
		capt2=capt2->next;
        temp3->next = NULL;
        delete temp3;
	}
	while (temp != NULL)
	{
		oldc=color[temp->destination.x][temp->destination.y];
		oldp=piece[temp->destination.x][temp->destination.y];
		oldc2=color[temp->origin.x][temp->origin.y];
		oldp2=piece[temp->origin.x][temp->origin.y];
		makeMove(temp);
		positionsTested++;
		if (isCheck(currentColor))
			val=-9999999;
			else
			val = -alphaBeta(depth - 1,-currentColor,-beta,-alpha);
		
		color[temp->destination.x][temp->destination.y]=oldc;
		piece[temp->destination.x][temp->destination.y]=oldp;
		color[temp->origin.x][temp->origin.y]=oldc2;
		piece[temp->origin.x][temp->origin.y]=oldp2;
        if (val >= beta)
		{
			while (temp2 != NULL)
			{
				temp3=temp2;
				temp2=temp2->next;
                temp3->next = NULL;
                delete temp3;
			}
			return beta;
		}
	    if (val > alpha)
	        alpha = val;
		temp=temp->next;
	}
	while (temp2 != NULL)
	{
		temp3=temp2;
		temp2=temp2->next;
        temp3->next = NULL;
        delete temp3;
	}
	return alpha;
}

int alphaBeta2(int depth,int currentColor)
{
    int n=1,val,best = -999999999;
	
    if (depth <= 0)
        return evaluate(currentColor);
	
	move good,*temp3,*temp2,*captures=NULL,*capt2;
	move *temp=generateLegalMoves(currentColor,&captures);

	int oldp,oldc,oldp2,oldc2;
	temp2=temp;
	capt2=captures;
	int totalmoves=countElements(temp2);
	printf("normalmoves: %d\n",totalmoves);
	totalmoves+=countElements(capt2);
	positionsTested=0;
	printf("processing (%d base moves): ",totalmoves);
	while (captures != NULL)
	{
		oldc=color[captures->destination.x][captures->destination.y];
		oldp=piece[captures->destination.x][captures->destination.y];
		oldc2=color[captures->origin.x][captures->origin.y];
		oldp2=piece[captures->origin.x][captures->origin.y];
		makeMove(captures);
		positionsTested++;
		if (isCheck(currentColor))
		{
			color[captures->destination.x][captures->destination.y]=oldc;
			piece[captures->destination.x][captures->destination.y]=oldp;
			color[captures->origin.x][captures->origin.y]=oldc2;
			piece[captures->origin.x][captures->origin.y]=oldp2;
			captures=captures->next;
			continue;
		}
		else
			val = -alphaBeta(depth - 1,-currentColor,-9999999,9999999);

		printf("%d%c.",n*100/totalmoves,37);
		color[captures->destination.x][captures->destination.y]=oldc;
		piece[captures->destination.x][captures->destination.y]=oldp;
		color[captures->origin.x][captures->origin.y]=oldc2;
		piece[captures->origin.x][captures->origin.y]=oldp2;
        if (val > best)
		{
            best = val;
			good.destination=captures->destination;
			good.origin=captures->origin;
			good.next=NULL;
		}
		captures=captures->next;
		n++;
	}
	while (capt2 != NULL)
	{
		temp3=capt2;
		capt2=capt2->next;
        temp3->next = NULL;
        delete temp3;
	}
	while (temp != NULL)
	{
		oldc=color[temp->destination.x][temp->destination.y];
		oldp=piece[temp->destination.x][temp->destination.y];
		oldc2=color[temp->origin.x][temp->origin.y];
		oldp2=piece[temp->origin.x][temp->origin.y];
		makeMove(temp);
		positionsTested++;
		if (isCheck(currentColor))
		{
			color[temp->destination.x][temp->destination.y]=oldc;
			piece[temp->destination.x][temp->destination.y]=oldp;
			color[temp->origin.x][temp->origin.y]=oldc2;
			piece[temp->origin.x][temp->origin.y]=oldp2;
			temp=temp->next;
			printf("%d%c.",n*100/totalmoves,37);
			continue;
		}
			else
			val = -alphaBeta(depth - 1,-currentColor,-9999999,9999999);
		printf("%d%c.",n*100/totalmoves,37);
		color[temp->destination.x][temp->destination.y]=oldc;
		piece[temp->destination.x][temp->destination.y]=oldp;
		color[temp->origin.x][temp->origin.y]=oldc2;
		piece[temp->origin.x][temp->origin.y]=oldp2;
        if (val > best)
		{
            best = val;
			good.destination=temp->destination;
			good.origin=temp->origin;
			good.next=NULL;
		}
		temp=temp->next;
		n++;
	}
	printf("\npositions tested: %d\n",positionsTested);
	while (temp2 != NULL)
	{
		temp3=temp2;
		temp2=temp2->next;
        temp3->next = NULL;
        delete temp3;
	}
	if (best<=-999999)
	{
		if (isCheck(currentColor))
		{
			printf("%s is CHECKMATED\n",currentColor==BLACK?"BLACK":"WHITE");
			exit(0);
		}
		printf("%s is STALLMATED\n",currentColor==BLACK?"BLACK":"WHITE");
		exit(0);
	}
	color[good.destination.x][good.destination.y]=color[good.origin.x][good.origin.y];
	piece[good.destination.x][good.destination.y]=piece[good.origin.x][good.origin.y];
	color[good.origin.x][good.origin.y]=0;
	piece[good.origin.x][good.origin.y]=0;
    return best;
}

/* ITERATIVE DEEPENING
int alphaBeta3(int depth,int currentColor)
{
    int val,best = -999999999;
	
    if (depth <= 0)
        return evaluate(currentColor);
	
	move good,*temp3,*temp2,*temp=generateLegalMoves(currentColor);
	int oldp,oldc;
	temp2=temp;
	while (temp != NULL)
	{
		oldc=color[temp->destination.x][temp->destination.y];
		oldp=piece[temp->destination.x][temp->destination.y];
		color[temp->destination.x][temp->destination.y]=color[temp->origin.x][temp->origin.y];
		piece[temp->destination.x][temp->destination.y]=piece[temp->origin.x][temp->origin.y];
		color[temp->origin.x][temp->origin.y]=0;
		piece[temp->origin.x][temp->origin.y]=0;
        
		val = -alphaBeta(depth - 1,-currentColor,-9999999,9999999);
		
		color[temp->origin.x][temp->origin.y]=color[temp->destination.x][temp->destination.y];
		piece[temp->origin.x][temp->origin.y]=piece[temp->destination.x][temp->destination.y];
		color[temp->destination.x][temp->destination.y]=oldc;
		piece[temp->destination.x][temp->destination.y]=oldp;
        if (val > best)
		{
            best = val;
			good.destination=temp->destination;
			good.origin=temp->origin;
			good.next=NULL;
		}
		temp=temp->next;
		
	}
	while (temp2 != NULL)
	{
		temp3=temp2;
		temp2=temp2->next;
        temp3->next = NULL;
        delete temp3;
	}
	color[good.destination.x][good.destination.y]=color[good.origin.x][good.origin.y];
	piece[good.destination.x][good.destination.y]=piece[good.origin.x][good.origin.y];
	color[good.origin.x][good.origin.y]=0;
	piece[good.origin.x][good.origin.y]=0;
    return best;
}
*/


void makeMove(move* temp)
{
	color[temp->destination.x][temp->destination.y]=color[temp->origin.x][temp->origin.y];
	piece[temp->destination.x][temp->destination.y]=piece[temp->origin.x][temp->origin.y];
	if ((piece[temp->destination.x][temp->destination.y]==PAWN)&&(((temp->destination.y==BOARD_SIZE-1)&&
		(color[temp->destination.x][temp->destination.y]==WHITE))||((temp->destination.y==0)&&
		(color[temp->destination.x][temp->destination.y]==BLACK))))
			piece[temp->destination.x][temp->destination.y]=QUEEN;
	updateCheck();
	color[temp->origin.x][temp->origin.y]=0;
	piece[temp->origin.x][temp->origin.y]=0;
}


void updateCheck()
{
	int i,j;
	position bKing, wKing;

	for (j=BOARD_SIZE-1;j>=0;j--)
	{
		for (i=0;i<BOARD_SIZE;i++)
		{
			if ((color[i][j]==BLACK)&&(piece[i][j]==KING))
			{
				bKing.x=i;
				bKing.y=j;
			}
			if ((color[i][j]==WHITE)&&(piece[i][j]==KING))
			{
				wKing.x=i;
				wKing.y=j;
			}
		}
	}
	isBlackCheck(bKing);
	isWhiteCheck(wKing);
}

void isBlackCheck(position bKing)
{
	move  *temp=NULL,*temp2,*temp3,*tempo;
	tempo=generateLegalMoves(WHITE,&temp);
	bCheck=false;
	temp2=temp;
	while (temp != NULL)
	{
		if ((temp->destination.x==bKing.x)&&(temp->destination.y==bKing.y))
			bCheck=true;	
		temp=temp->next;
	}
	while (temp2 != NULL)
	{
		temp3=temp2;
		temp2=temp2->next;
        temp3->next = NULL;
        delete temp3;
	}
	while (tempo != NULL)
	{
		temp3=tempo;
		tempo=tempo->next;
        temp3->next = NULL;
        delete temp3;
	}
}

void isWhiteCheck(position wKing)
{
	move  *temp=NULL,*temp2,*temp3,*tempo;
	tempo=generateLegalMoves(BLACK,&temp);
	wCheck=false;
	temp2=temp;
	while (temp != NULL)
	{
		if ((temp->destination.x==wKing.x)&&(temp->destination.y==wKing.y))
			wCheck=true;	
		temp=temp->next;
	}
	while (temp2 != NULL)
	{
		temp3=temp2;
		temp2=temp2->next;
        temp3->next = NULL;
        delete temp3;
	}
	while (tempo != NULL)
	{
		temp3=tempo;
		tempo=tempo->next;
        temp3->next = NULL;
        delete temp3;
	}
}

bool isCheck(int currentColor)
{
	updateCheck();
	if (currentColor==BLACK)
		return bCheck;
	return wCheck;
}


int countElements(move* temp)
{

	move* temp2=temp;
	int n=0;
	
	while (temp2 != NULL)
	{
		n++;
		temp2=temp2->next;
	}

	return n;

}