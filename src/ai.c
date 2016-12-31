#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "cchess.h"
#include "ai.h"
#include "gameState.h"
#include "valid.h"
#include "piece.h"
#include "linkedList.h"
#include "move.h"

// Function for evaluating a game to determine who is winning
// Positive number = current turn winning
// Negative number = current turn losing
// The higher the better
double eval(GameState *game, int depth)
{
	// At depth zero, evaluate and return score
	if (depth == 0)
	{
		double score = 0;

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
		LinkedList *currentPieceList = pieces;
		Move *headMove = createMove(-1, -1, -1, -1);
		LinkedList *allMoves = createList(headMove, NULL);
		LinkedList *pieceMoves;
		PiecePos *currentPiece;

		// Loop through pieces
		while (currentPieceList != NULL && currentPieceList->data != NULL)
		{
			currentPiece = currentPieceList->data;

			// Get all moves for that piece
			pieceMoves = findMoves(game, currentPiece);

			// Add moves to collection of all moves
			allMoves = listConcat(allMoves, pieceMoves);

			// Move to next piece
			currentPieceList = currentPieceList->next;
		}

		freePiecePosList(pieces);

		int moves = 0;
		LinkedList *currentMove = allMoves->next;
		GameState *new;
		char move[4];
		double score = 0, tempScore;

		while (currentMove != NULL && currentMove->data != NULL)
		{
			// Create a copy of the current game state
			new = createGameState(game);

			// Play move
			moveToChar(currentMove->data, move);
			makeMove(move, new->board);	

			// Simulate next player's turn
			new->turn ^= 1;
		
			// Decrease depth and evaluate new state
			tempScore = eval(new, depth - 1);
			score += tempScore;
			moves++;
#ifdef DEBUG
			//printf("Player %d Testing move: %.4s Score: %f\n", new->turn, move, tempScore);
#endif

			freeGameState(new);

			currentMove = currentMove->next;
		}

		freeMoveList(allMoves);

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
				// Store piece position in structure
				temp = createPiecePos(rank, file);
				
				// Add piece position to list
				results = listPush(results, temp);

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
	LinkedList *results = NULL;
	//LinkedList *current = results;
	Move *tempMove, *copyTempMove;
	char charTempMove[4];
	int direction;
	Piece *piece = game->board->board[piecePos->rank][piecePos->file];

	// Possible moves for a pawn
	static int pawnMoves[4][2] = {{1, -1}, {1, 0}, {1, 1}, {2, 0}};

	// Possible moves for a knight
	static int knightMoves[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};

	// Possible moves for a king
	static int kingMoves[8][2] = {{1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};

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

			// Check four possible moves
			for (int i = 0; i < 4; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + (direction * pawnMoves[i][0]),
						piecePos->file + pawnMoves[i][1]);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		case KNIGHT:

			// Check all 8 possible moves for a knight

			for (int i = 0; i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + knightMoves[i][0],
						piecePos->file + knightMoves[i][1]);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		case BISHOP: 

			// Check diagonal moves

			for (int i = 0; (piecePos->rank + i < 8) && (piecePos->file + i < 8); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank - i >= 0) && (piecePos->file - i >= 0); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank - i >= 0) && (piecePos->file + i < 8); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank + i < 8) && (piecePos->file - i >= 0); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		case ROOK: 

			// Check vertical moves

			for (int i = 0; piecePos->rank + i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; piecePos->rank - i >= 0; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			// Check horizontal moves

			for (int i = 0; piecePos->file + i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; piecePos->file - i >= 0; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		case QUEEN: 

			// Check diagonal moves

			for (int i = 0; (piecePos->rank + i < 8) && (piecePos->file + i < 8); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank - i >= 0) && (piecePos->file - i >= 0); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank - i >= 0) && (piecePos->file + i < 8); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; (piecePos->rank + i < 8) && (piecePos->file - i >= 0); i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			// Check vertical moves

			for (int i = 0; piecePos->rank + i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + i,
						piecePos->file);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; piecePos->rank - i >= 0; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank - i,
						piecePos->file);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			// Check horizontal moves

			for (int i = 0; piecePos->file + i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank,
						piecePos->file + i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			for (int i = 0; piecePos->file - i >= 0; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank,
						piecePos->file - i);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		case KING: 

			// Check all 8 possible moves for a king

			for (int i = 0; i < 8; i++)
			{
				tempMove = createMove(piecePos->rank,
						piecePos->file,
						piecePos->rank + kingMoves[i][0],
						piecePos->file + kingMoves[i][1]);

				moveToChar(tempMove, charTempMove);

				if (validMove(charTempMove, game->turn, game->board))
				{
					copyTempMove = copyMove(tempMove);
					results = listPush(results, copyTempMove);
				}

				free(tempMove);
			}

			break;
		default: 
			printf("Error: piece type not recognized %d\n", piece->type);
			exit(EXIT_FAILURE);
	}

	return results;
}

void findMove(GameState *game, char move[4], int turn, int depth)
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
	LinkedList *currentPieceList = pieces;
	//Move *headMove = createMove(-1, -1, -1, -1);
	LinkedList *allMoves = NULL;
	LinkedList *pieceMoves;
	PiecePos *currentPiece;

	// Loop through pieces
	while (currentPieceList != NULL && currentPieceList->data != NULL)
	{
		currentPiece = currentPieceList->data;

		// Get all moves for that piece
		pieceMoves = findMoves(game, currentPiece);
		
		// Add moves to collection of all moves
		allMoves = listConcat(allMoves, pieceMoves);

		// Move to next piece
		currentPieceList = currentPieceList->next;
	}

	freePiecePosList(pieces);

	LinkedList *currentMove = allMoves;

#ifdef DEBUGZ
	while (currentMove != NULL && currentMove->data != NULL)
	{
		printMove(currentMove->data);
		currentMove = currentMove->next;
	}

	currentMove = allMoves;
#endif

	GameState *new;
	char tempMove[4], bestMove[4];
	int bestScore = INT_MIN;
	double score;

	while (currentMove != NULL && currentMove->data != NULL)
	{
		// Create a copy of the current game state
		new = createGameState(game);
			
		// Play move
		moveToChar(currentMove->data, tempMove);
		makeMove(tempMove, new->board);	

		// Simulate next turn
		new->turn ^= 1;

		// Recursively evaluate that state
		score = eval(new, depth);

#ifdef DEBUG
		//printf("Testing move %.4s, Score: %f\n", tempMove, score);
#endif

		if (score > bestScore)
		{
			bestScore = score;
			strncpy(bestMove, tempMove, 4);
#ifdef DEBUG
			//printf("New best move: %.4s\n", bestMove);
#endif
		}

		freeGameState(new);

		currentMove = currentMove->next;
	}

	freeMoveList(allMoves);

	if (bestScore == INT_MIN)
	{
		printf("findMove: Error: no valid moves found\n");
		exit(EXIT_FAILURE);
	}
	
	//printf("Best move: %.4s\n", bestMove);
	strncpy(move, bestMove, 4);

#endif
}
