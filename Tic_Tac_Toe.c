/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 6														*/
/*	Topic: Tic Tac Toe													*/
/*	File name: Tic_Tac_Toe												*/
/*	Date: 4/26/2016														*/
/*	Objective:	Develop a 4x4 tic-tac-toe game							*/
/*	Comments:															*/
/************************************************************************/				

#include <stdio.h>

/***** #defines *****/
#define DIM 4

/***** global variables *****/
typedef const char Player;
Player PLAYER_1 = 'X';
Player PLAYER_2 = '0';

typedef char Board[DIM][DIM];
Board BOARD;

FILE *pFile;

/***** function definitions *****/
// this function initializes the board before game starts...
void InitializeBoard(Board BOARD)
{
	unsigned int row, column;

	for(row=0; row < DIM; row++)
	{
		for(column=0; column < DIM; column++)
		{
			BOARD[row][column] = '_';
		}
	}
}

// this function prints the board contents...
void PrintBoard(Board BOARD)
{
	unsigned int row, column; 

	for(row=0; row < DIM; row++)
	{
		for(column=0; column < DIM; column++)
		{
			printf("[%u,%u] ", row, column);
			fprintf(pFile, "[%u,%u] ", row, column);

			if(column == DIM-1) { printf("\n"); fprintf(pFile, "\n"); }
		}
	}
	
	for(row=0; row < DIM; row++)
	{
		for(column=0; column < DIM; column++)
		{
			if(BOARD[row][column] == '_') { printf("  %c   ", BOARD[row][column]); fprintf(pFile, "  %c   ", BOARD[row][column]); }
			else						  { printf("  %c   ", BOARD[row][column]); fprintf(pFile, "  %c   ", BOARD[row][column]); }

			if(column == DIM-1) { printf("\n"); fprintf(pFile, "\n"); }
		}
	}
}

// this function prompts the player to play his next move
// Function returns a 1 if the player made a correct and valid move, 0 otherwise
// If function returns a 0, it prompts the player again to make a correct move until he does
unsigned int NextPlayerPlays(unsigned int Move, Board BOARD)
{
	unsigned int MoveOK = 0;
	unsigned int row, column;

	while(!MoveOK)
	{
		// Prompts the player to make his next move
		if(Move % 2) { printf("\nPlayer 1 plays..."); fprintf(pFile, "\nPlayer 1 plays..."); }
		else		 { printf("\nPlayer 2 plays..."); fprintf(pFile, "\nPlayer 2 plays..."); }

		printf("\nEnter the row# to play   : ");
		scanf("%u", &row);
		fprintf(pFile, "\nEnter the row# to play   : %u", row);
		printf("Enter the column# to play: ");
		scanf("%u", &column);
		fprintf(pFile, "\nEnter the column# to play: %u", column);
		printf("\n");
		fprintf(pFile, "\n\n");

		// check if row or column entered by user exceeds the board dimensions or
		// a player is trying to overwrite an already placed 'X' or '0'
		if((row >= DIM) || (column >= DIM)) 
		{
			MoveOK = 0;
			printf("Incorrect selection of row and/or column\n");
			fprintf(pFile, "Incorrect selection of row and/or column\n");

		}
		else if((BOARD[row][column] == 'X') || (BOARD[row][column] == '0')) 
		{
			MoveOK = 0;
			printf("Incorrect selection of row and/or column\n");
			fprintf(pFile, "Incorrect selection of row and/or column\n");
		}
		else 
		{
			MoveOK = 1;
			if(Move % 2) BOARD[row][column] = PLAYER_1;
			else		 BOARD[row][column] = PLAYER_2;
		}
	}

	return MoveOK;
}

// this function checks if a player has won the game. 
// Returns 1 if player has DIM pieces in a row, horizontally, vertically, or diagonally.
unsigned int DidPlayerWin(unsigned int Move, Board BOARD)
{
	unsigned int PlayerWins = 0;
	unsigned int Full = 0;
		
	Full = IsAnyRowFull(BOARD);
	PlayerWins += Full;
	Full = IsAnyColumnFull(BOARD);
	PlayerWins += Full;
	Full = IsMajorDiagonalFull(BOARD);
	PlayerWins += Full;
	Full = IsMinorDiagonalFull(BOARD);
	PlayerWins += Full;

	if(PlayerWins > 0)
	{
		if(Move % 2) { printf("Player 1 won!"); fprintf(pFile, "Player 1 won!"); }
		else		 { printf("Player 2 won!"); fprintf(pFile, "Player 2 won!"); }
	}

	return ((PlayerWins > 0) ? 1 : 0);
}

// this function checks if the board is full and no more plays can be made
// Returns 1 if board is full, 0 otherwise
unsigned int IsBoardFull(unsigned int Move, Board BOARD)
{
	unsigned int BoardFull = 0;

	if(Move >= DIM*DIM) BoardFull = 1;

	return BoardFull;
}

// this function checks if a row is full
// Function returns 1 if there are DIM pieces of type player in row, 0 otherwise.
unsigned int IsRowFull(unsigned int Row_No, Board BOARD)
{
	unsigned int RowFull = 1;
	int column;

	for(column=0; column <= DIM-2; column++)
	{
		if (BOARD[Row_No][column] != BOARD[Row_No][column+1]) RowFull = 0;
	}

	for(column=0; column < DIM; column++)
	{
		if (BOARD[Row_No][column] == '_') RowFull = 0;
	}

	return RowFull;
}

// this function checks if any row of the board is full
unsigned int IsAnyRowFull(Board BOARD)
{
	unsigned int AnyRowFull = 0;
	unsigned int RowFull = 0;
	int row;

	for(row=0; row < DIM; row++)
	{
		RowFull = IsRowFull(row, BOARD);
		AnyRowFull += RowFull;
	}

	return ((AnyRowFull > 0) ? 1 : 0);
}

// this function checks if a column is full
// Function returns 1 if there are DIM pieces of type player in column, 0 otherwise.
unsigned int IsColumnFull(unsigned int Column_No, Board BOARD)
{
	unsigned int ColumnFull = 1;
	int row;

	for(row=0; row <= DIM-2; row++)
	{
		if(BOARD[row][Column_No] != BOARD[row+1][Column_No]) ColumnFull = 0;
	}

	for(row=0; row < DIM; row++)
	{
		if(BOARD[row][Column_No] == '_') ColumnFull = 0;
	}

	return ColumnFull;
}

// this function checks if any column of the board is full
unsigned int IsAnyColumnFull(Board BOARD)
{
	unsigned int AnyColumnFull = 0;
	unsigned int ColumnFull = 0;
	int column;

	for(column=0; column < DIM; column++)
	{
		ColumnFull = IsColumnFull(column, BOARD);
		AnyColumnFull += ColumnFull;
	}

	return ((AnyColumnFull > 0) ? 1 : 0);
}

// this function checks if the major diagonal is full
unsigned int IsMajorDiagonalFull(Board BOARD)
{
	unsigned int MajorDiagonalFull = 1;
	int i;

	for(i=0; i < DIM-2; i++)
	{
		if(BOARD[i][i] != BOARD[i+1][i+1]) MajorDiagonalFull = 0;
	}

	for(i=0; i < DIM; i++)
	{
		if(BOARD[i][i] == '_') MajorDiagonalFull = 0;		
	}

	return MajorDiagonalFull;
}

// this function checks if the minor diagonal is full
unsigned int IsMinorDiagonalFull(Board BOARD)
{
	unsigned int MinorDiagonalFull = 1;
	int i, j;

	for(i=0, j=DIM-1; i < DIM-2; i++, j--)
	{
		if(BOARD[i][j] != BOARD[i+1][j-1]) MinorDiagonalFull = 0;
	}

	for(i=0, j=DIM-1; i <= DIM; i++, j--)
	{
		if(BOARD[i][j] == '_') MinorDiagonalFull = 0;		
	}

	return MinorDiagonalFull;
}

/***** main() *****/
int main()
{
	unsigned int Move, BoardFull, Win;
	int i, j, found;

	// open file to write
	pFile = fopen ("Tic_Tac_Toe.txt", "w");
	if (pFile == NULL)	printf("Error opening file"); 

	Move = 1;
	BoardFull = 0;
	Win = 0;

	printf("Game begins...\n"); 
	fprintf(pFile, "Game begins...\n\n");
	InitializeBoard(BOARD);						// initialize the board
	PrintBoard(BOARD);							// print board contents

	while(!Win && !BoardFull)					// play until a player wins or the baord is full
	{
		NextPlayerPlays(Move, BOARD);			// prompt the next player to play
		PrintBoard(BOARD);						// print board contents
		
		Win = DidPlayerWin(Move, BOARD);		// check if a player won
		BoardFull = IsBoardFull(Move, BOARD);	// check if the board is full

		if((!Win) && (BoardFull)) { printf("It's a draw!"); fprintf(pFile, "It's a draw!"); }

		Move++;
	}

	fprintf(pFile, "\nGame Over");
	// close the I/O file
	fclose (pFile);

	printf("\nGame Over. (Press any key and hit [enter] to exit)");
	scanf("%d", &i);
	return;
}