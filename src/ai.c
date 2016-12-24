#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cchess.h"
#include "ai.h"
#include "gameState.h"
#include "valid.h"
#include "piece.h"
#include "linkedList.h"

// Function for evaluating a game to determine who is winning
// Positive number = current turn winning
// Negative number = current turn losing
// The higher the better
int eval(GameState *game, int depth)
{
	// At depth zero, evaluate and return score
	if (depth == 0)
	{
		int score = 0;

		Piece *temp;

		// Go through board
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)	
			{
				temp = game->board->board[i][j];

				if (temp != NULL)
				{
					if (temp->color == game->turn)
						score += pointVal(temp);
					else
						score -= pointVal(temp);
				}
			}
		}

		return score;
	}
	else
	{
		// Recusive step
		// Find the average of playing and evaluating all possible moves

		// Get all of current players pieces
		LinkedList *pieces = findPieces(game, game->turn);
		
		LinkedList *currentPiece = pieces->next;
		LinkedList *allMoves;
		LinkedList *pieceMoves;

		// Loop through pieces
		while (currentPiece != NULL)
		{
			// Get all moves for that piece
			pieceMoves = findMoves(game, currentPiece->data);

			// Add moves to collection of all moves
			allMoves = listConcat(allMoves, pieceMoves);

			// Move to next piece
			currentPiece = currentPiece->next;
		}

		int moves = 0;
		LinkedList *currentMove = allMoves->next;
		GameState *new;
		char move[4];
		int score = 0;

		while (currentMove != NULL)
		{
			// Create a copy of the current game state
			new = createGameState(game);

			// Play move
			moveToChar(currentMove->data, move);
			makeMove(move, new->board);	
		
			// Decrease depth and evaluate new state
			score += eval(new, depth - 1);
			moves++;
		}

		// Return average score of moves
		return score / moves;
	}
}

// Find all of a player's pieces
// Return in linked list
LinkedList * findPieces(GameState *game, int turn)
{
	// Create a list to store result
	LinkedList *results = createList(NULL, NULL);
	/*LinkedList *current = results;*/
	PiecePos *temp; 
	
	// Traverse board looking for players pieces
	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			if (game->board->board[rank][file] && game->board->board[rank][file]->color == turn)
			{
				// Store piece position in stucture
				temp = createPiecePos(rank, file);
				
				// Add piece position to list
				listAppend(results, temp);

				// Advance list
				//current = current->next;
			}
		}
	}

	return results;
}

// Find all the moves a piece can make
LinkedList * findMoves(GameState *game, PiecePos *piecePos)
{
	// Create a list to store result	
	LinkedList *results = createList(NULL, NULL);
	//LinkedList *current = results;
	Move *tempMove, *copyTempMove;
	char charTempMove[4];

			int direction;
	Piece *piece = game->board->board[piecePos->rank][piecePos->file];

	switch (piece->type)
	{
		case PAWN:
			// Switch move direction based on turn
			if (game->turn == WHITE) 
			{
				direction = -1;
			}
			else
			{
				direction = 1;
			}

			// Check three forward moves
			for (int i = -1; i <= 1; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + direction,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					listAppend(results, copyTempMove);
				}

				free(tempMove);
			}
			
			// Check forward double move
			tempMove = createMove(piecePos->rank,
					piecePos->file,
					piecePos->rank + 2*direction,
					piecePos->file);

			moveToChar(tempMove, charTempMove);

			if (validMove(charTempMove, game->turn, game->board))
			{
				copyTempMove = copyMove(tempMove);
				listAppend(results, copyTempMove);
			}

			free(tempMove);

			break;
		case KNIGHT:

			break;
		case BISHOP: 

			break;
		case ROOK: 

			break;
		case QUEEN: 

			break;
		case KING: 

			break;
		default: 
			printf("Error: piece type not recognized %d\n", piece->type);
			exit(EXIT_FAILURE);
	}

	return results;
}

void findMove(GameState *game, char move[4], int turn)
{
#ifdef DUMB_AI
	// Setup some variables.
	int randMove[4];
	move[0] = '?';

	// Generate random moves until a valid one is found.
	while (validMove(move, turn, game->board) != 1)
	{
		// Make some random integers for the move
		randMove[0] = (rand() % 8) + 97;
		randMove[1] = (rand() % 8) + 49;
		randMove[2] = (rand() % 8) + 97;
		randMove[3] = (rand() % 8) + 49;

		// Combine them to make a move.
		move[0] = (char)randMove[0];
		move[1] = (char)randMove[1];
		move[2] = (char)randMove[2];
		move[3] = (char)randMove[3];
	}
#endif
#ifdef SMART_AI

	// Get all of current players pieces
	LinkedList *pieces = findPieces(game, turn);
	LinkedList *currentPieceList = pieces->next;
	Move *headMove = createMove(-1, -1, -1, -1);
	LinkedList *allMoves = createList(headMove, NULL);
	LinkedList *pieceMoves;
	PiecePos *currentPiece;

	// Loop through pieces
	while (currentPieceList != NULL)
	{
		currentPiece = currentPieceList->data;

		// Get all moves for that piece
		pieceMoves = findMoves(game, currentPiece);
		
		// Add moves to collection of all moves
		allMoves = listConcat(allMoves, pieceMoves);

		// Move to next piece
		currentPieceList = currentPieceList->next;
	}

	LinkedList *currentMove = allMoves->next;

#ifdef DEBUG
	while (currentMove != NULL)
	{
		printMove(currentMove->data);
		currentMove = currentMove->next;
	}
#endif

	currentMove = allMoves->next;

	GameState *new;
	char tempMove[4], bestMove[4];
	int bestScore = -1;
	int score;

	while (currentMove != NULL)
	{
		// Create a copy of the current game state
		new = createGameState(game);
			
		// Play move
		moveToChar(currentMove->data, tempMove);
		makeMove(tempMove, new->board);	

		// Recursively evaluate that state
		score = eval(new, 0);
		printf("Testing move %s, Score: %d\n", tempMove, score);

		if (score > bestScore)
		{
			bestScore = score;
			strncpy(bestMove, tempMove, 4);
			printf("New best move: %s\n", bestMove);
		}

		freeGameState(new);

		currentMove = currentMove->next;
	}

	if (bestScore == -1)
	{
		printf("findMove: Error: no valid moves found\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Best move: %s\n", bestMove);
	strncpy(move, bestMove, 4);

#endif
}
