#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "piece.h"

// Create a board
Board * createBoard()
{
	// Allocate a board
	Board *new = calloc(1, sizeof(Board));

	// Place starting pieces
	new->board[0][0] = createPiece(ROOK, BLACK);
	new->board[0][1] = createPiece(KNIGHT, BLACK);
	new->board[0][2] = createPiece(BISHOP, BLACK);
	new->board[0][3] = createPiece(QUEEN, BLACK);
	new->board[0][4] = createPiece(KING, BLACK);
	new->board[0][5] = createPiece(BISHOP, BLACK);
	new->board[0][6] = createPiece(KNIGHT, BLACK);
	new->board[0][7] = createPiece(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
		new->board[1][i] = createPiece(PAWN, BLACK);
	
	new->board[7][0] = createPiece(ROOK, WHITE);
	new->board[7][1] = createPiece(KNIGHT, WHITE);
	new->board[7][2] = createPiece(BISHOP, WHITE);
	new->board[7][3] = createPiece(QUEEN, WHITE);
	new->board[7][4] = createPiece(KING, WHITE);
	new->board[7][5] = createPiece(BISHOP, WHITE);
	new->board[7][6] = createPiece(KNIGHT, WHITE);
	new->board[7][7] = createPiece(ROOK, WHITE);

	for (int i = 0; i < 8; i++)
		new->board[6][i] = createPiece(PAWN, WHITE);

	// The rest of the board will be filled with NULLs due to calloc

	return new;
}

// Free a board
void freeBoard(Board *board)
{
	// Free each of the pieces
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			freePiece(board->board[i][j]);

	// Free the whole board
	free(board);
}

// Create a replica of a board
Board * copyBoard(Board *board)
{
	Board *copy = calloc(1, sizeof(Board));

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			copy->board[i][j] = copyPiece(board->board[i][j]);
		}
	}

	return copy;
}

/*
	Function: render
	Prints the board in a easy to understand manner.
	Takes a pointer to the board.
	Returns nothing.
*/

void renderBoard(Board *board)
{
	// Clears the screen.
	/*system("clear");*/

	// Draw each of the pieces
	Piece * p;

	// Draw files
	printf("     a   b   c   d   e   f   g   h \n");
	printf("    --- --- --- --- --- --- --- ---\n");

	for (int i = 0; i < 8; i++)
	{
		// Draw ranks
		printf(" %d |", 8 - i);

		for (int j = 0; j < 8; j++)
		{
			// Get the piece at that position
			p = board->board[i][j];

			if (p == NULL)
				printf("   ");
			else
				printf(" %c ", pieceToChar(p));

			printf("%s", "|");
		}

		printf("\n    --- --- --- --- --- --- --- ---\n");
	}
}

Move * createMove(
		unsigned char startRank,
		unsigned char startFile,
		unsigned char endRank,
		unsigned char endFile
	)
{
	Move *new = malloc(sizeof(Move));

	new->startRank = startRank;
	new->startFile = startFile;
	new->endRank = endRank;
	new->endFile = endFile;
	
	return new;
}

void freeMove(Move *move)
{
	free(move);
}

Move * copyMove(Move *orig)
{
	Move *copy = createMove(orig->startRank, orig->startFile, orig->endRank, orig->endFile);
	return copy;
}

void printMove(Move *move)
{
	printf("%d %d %d %d\n", move->startRank, move->startFile, move->endRank, move->endFile);
}
