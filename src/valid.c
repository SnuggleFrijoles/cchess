#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cchess.h"
#include "board.h"
#include "piece.h"
#include "valid.h"

/*
Function: validMove
Determines if a move is valid.
Takes parameter string of move.
Returns either a 1 or 0 depending of if the move is valid.
*/

int validMove(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Check to see if the start and end positions are valid.
	if (startFile < 0 | startFile > 7)
	{
		/*printf("Start file must be between a and h: %d\n", startFile + 1);*/
		return 0;
	}
	if (startRank < 0 | startRank > 7)
	{
		/*printf("Start rank must be between 1 and 8: %d\n", startRank + 1);*/
		return 0;
	}
	if (endFile < 0 | endFile > 7)
	{
		/*printf("End file must be between a and h: %d\n", endFile + 1);*/
		return 0;
	}
	if (endRank < 0 | endRank > 7)
	{
		/*printf("End rank must be between 1 and 8: %d\n", endRank + 1);*/
		return 0;
	}

	// Get the piece being moved.
	Piece *piece = board->board[startRank][startFile];
	Piece *destination = board->board[endRank][endFile];

	// Check if piece real
	if (piece == NULL)
		return 0;

	// Check to see if the wrongly owned piece is being moved.
	if (piece->color != turn)
	{
		/*printf("Can't move opponents pieces!\n");*/
		return 0;
	}

	// Don't allow friendly fire.
	if (destination != NULL && destination->color == turn)
	{
		/*printf("You shouldn't take your own pieces\n");*/
		return 0;
	}

	// Call appropriate function
	if (piece->type == PAWN)
		return validPawn(move, turn, board);
	else if (piece->type == ROOK)
		return validRook(move, turn, board);
	else if (piece->type == KNIGHT)
		return validKnight(move, turn, board);
	else if (piece->type == BISHOP) 
		return validBishop(move, turn, board);
	else if (piece->type == QUEEN)
		return validQueen(move, turn, board);
	else if (piece->type == KING)
		return validKing(move, turn, board);

	return 0;
}

int validPawn(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	Piece *destination = board->board[endRank][endFile];

	// Check to see if moving or attacking
	if (destination == NULL) 
	{
		// Must not change files
		if (endFile - startFile == 0)
		{
			switch (turn)
			{
				case WHITE:
					// Allow two space move from starting position if nothing in the way.
					if (endRank - startRank == -2 && startRank == 6 && board->board[5][startFile] == NULL)
						return 1;
					// Allow standard one space forward move.
					else
						return (endRank - startRank == -1);
				case BLACK:
					// Allow two space move from starting position if nothing in the way.
					if (endRank - startRank == 2 && startRank == 1 && board->board[2][startFile] == NULL)
						return 1;
					// Allow standard one space forward move.
					else 
						return (endRank - startRank == 1);
				default:
					return 0;
			}
		}
		else
			return 0;
	}
	else
	{
		// Only allow diagonal attacks
		if (abs(endFile - startFile) == 1)
		{
			if (turn == WHITE)
				return (endRank - startRank == -1);
			else
				return (endRank - startRank == 1);
		}
		else
			return 0;
	}
}

int validRook(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);
	
	// Rooks must move horizontally
	if (endRank == startRank)
	{
		// Check to make sure there are no pieces in between the start and end positions.
		if (endFile > startFile)
		{
			for (int i = startFile + 1; i < endFile; i++)
			{
				if (board->board[startRank][i] != NULL)
					return 0;
			}
			return 1;
		}
		else
		{
			for (int i = startFile - 1; i > endFile; i--)
			{
				if (board->board[startRank][i] != NULL)
					return 0;
			}
			return 1;
		}
	}
	// or vertically.
	else if (endFile == startFile)
	{
		// Check to make sure there are no pieces in between the start and end positions.
		if (endRank > startRank)
		{
			for (int i = startRank + 1; i < endRank; i++)
			{
				if (board->board[i][startFile] != NULL)
					return 0;
			}
			return 1;
		}
		else
		{
			for (int i = startRank - 1; i > endRank; i--)
			{
				if (board->board[i][startFile] != NULL)
					return 0;
			}
			return 1;
		}
	}
	else
		return 0;

}

int validKnight(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Only allow proper knight moves.
	if (endRank - startRank == 1 && endFile - startFile == 2)
		return 1;
	else if (endRank - startRank == 1 && endFile - startFile == -2)
		return 1;
	else if (endRank - startRank == -1 && endFile - startFile == 2)
		return 1;
	else if (endRank - startRank == -1 && endFile - startFile == -2)
		return 1;
	else if (endRank - startRank == 2 && endFile - startFile == 1)
		return 1;
	else if (endRank - startRank == 2 && endFile - startFile == -1)
		return 1;
	else if (endRank - startRank == -2 && endFile - startFile == 1)
		return 1;
	else if (endRank - startRank == -2 && endFile - startFile == -1)
		return 1;
	else
		return 0;
}

int validBishop(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Only allow diagonal moves.
	if (endFile - startFile == endRank - startRank | endFile - startFile == -(endRank - startRank))
	{
		// Get the direction of the move.
		int xdir = endFile - startFile;
		int ydir = endRank - startRank;

		// Make sure no pieces are in the way.
		if (xdir > 0 && ydir > 0)
		{
			for (int i = 1; i < endFile - startFile; ++i)
			{
				if (board->board[startRank+i][startFile+i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir > 0 && ydir < 0)
		{
			for (int i = 1; i < endFile - startFile; ++i)
			{
				if (board->board[startRank-i][startFile+i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir < 0 && ydir > 0)
		{
			for (int i = 1; i < -(endFile - startFile); ++i)
			{
				if (board->board[startRank+i][startFile-i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir < 0 && ydir < 0)
		{
			for (int i = 1; i < -(endFile - startFile); ++i)
			{
				if (board->board[startRank-i][startFile-i] != 0)
					return 0;
			}
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int validQueen(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Allow diagonal moves.
	if (endFile - startFile == endRank - startRank | endFile - startFile == -(endRank - startRank))
	{
		// Get the direction of the move.
		int xdir = endFile - startFile;
		int ydir = endRank - startRank;

		// Make sure no pieces are in the way.
		if (xdir > 0 && ydir > 0)
		{
			for (int i = 1; i < endFile - startFile; ++i)
			{
				if (board->board[startRank+i][startFile+i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir > 0 && ydir < 0)
		{
			for (int i = 1; i < endFile - startFile; ++i)
			{
				if (board->board[startRank-i][startFile+i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir < 0 && ydir > 0)
		{
			for (int i = 1; i < -(endFile - startFile); ++i)
			{
				if (board->board[startRank+i][startFile-i] != 0)
					return 0;
			}
			return 1;
		}
		else if (xdir < 0 && ydir < 0)
		{
			for (int i = 1; i < -(endFile - startFile); ++i)
			{
				if (board->board[startRank-i][startFile-i] != 0)
					return 0;
			}
			return 1;
		}
		else
			return 0;
	}
	// or horizontal moves.
	else if (endRank - startRank == 0)
	{
		// Check to make sure there are no pieces in between the start and end positions.
		if (endFile > startFile)
		{
			for (int i = startFile + 1; i < endFile; i++)
			{
				if (board->board[startRank][i] != 0)
					return 0;
			}
			return 1;
		}
		else
		{
			for (int i = startFile - 1; i > endFile; i--)
			{
				if (board->board[startRank][i] != 0)
					return 0;
			}
			return 1;
		}
	}
	// or vertically.
	else if (endFile - startFile == 0)
	{
		// Check to make sure there are no pieces in between the start and end positions.
		if (endRank > startRank)
		{
			for (int i = startRank + 1; i < endRank; i++)
			{
				if (board->board[i][startFile] != 0)
					return 0;
			}
			return 1;
		}
		else
		{
			for (int i = startRank - 1; i > endRank; i--)
			{
				if (board->board[i][startFile] != 0)
					return 0;
			}
			return 1;
		}
	}
	else
		return 0;
}

int validKing(char move[4], int turn, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	if (endFile - startFile > 1 | endFile - startFile < -1)
		return 0;
	else if (endRank - startRank > 1 | endRank - startRank < -1)
		return 0;
	else
		return 1;
}

void moveToChar(Move *move, char moveResult[4])
{
#if 0
	if (move->startRank < 0 || move->startRank > 7)
	{
		printf("moveToChar: Error: startRank out of range %d\n", move->startRank);
//		exit(EXIT_FAILURE);
	}
	
	if (move->endRank < 0 || move->endRank > 7)
	{
		printf("moveToChar: Error: endRank out of range %d\n", move->endRank);
//		exit(EXIT_FAILURE);
	}
	
	if (move->startFile < 0 || move->startFile > 7)
	{
		printf("moveToChar: Error: startFile out of range %d\n", move->startFile);
//		exit(EXIT_FAILURE);
	}
	
	if (move->endFile < 0 || move->endFile > 7)
	{
		printf("moveToChar: Error: endFile out of range %d\n", move->endFile);
//		exit(EXIT_FAILURE);
	}
#endif
	moveResult[0] = 'a' + move->startFile;
	moveResult[1] = '8' - move->startRank;
	moveResult[2] = 'a' + move->endFile;
	moveResult[3] = '8' - move->endRank;
}
