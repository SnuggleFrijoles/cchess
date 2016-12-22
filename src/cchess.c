#include <stdio.h>		// argc, argv
#include <stdlib.h>		// rand, srand
#include <string.h>		// strncmp
#include <time.h>		// time

#include "cchess.h"
#include "board.h"
#include "piece.h"
#include "gameState.h"
#include "ai.h"
#include "valid.h"


/*
Function: delay
A simple function to delay time.
Takes an amount of milliseconds as a parameter.
Returns nothing.
*/

void delay(int milliseconds)
{
	long pause;
	clock_t now,then;

	// Determines how long the pause should be as an amount of processor ticks.
	pause = milliseconds*(CLOCKS_PER_SEC/1000);
	now = then = clock();

	// Loops until the correct amout of processor ticks has been achieved.
	while( (now-then) < pause )
		now = clock();
}


/*
Function: isCheckmate
Checks to see if a valid move is checkmate
Takes parameters string of move and a pointer to the board.
Returns either a 1 or 0 depeding on if it is checkmate.
*/

int isCheckmate(char move[4], int turn, Board *board)
{
	// Get the integer values for end position of move.
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Check to see if the end position is a king.
	if (board->board[endRank][endFile] != NULL)
		return (board->board[endRank][endFile]->type == KING);
	else
		return 0;
}

/*
Function: makeMove
Conducts a valid move.
Takes parameters string of move and a pointer to the board.
Returns nothing.
*/

void makeMove(char *move, Board *board)
{
	// Get the integer values for the move.
	int startFile = move[0] - 97;
	int startRank = 8 - (move[1] - 48);
	int endFile = move[2] - 97;
	int endRank = 8 - (move[3] - 48);

	// Conduct the move.
	board->board[endRank][endFile] = board->board[startRank][startFile];
	board->board[startRank][startFile] = NULL;
}

/*
Function: main
Runs the game then frees all memory.
Takes standard parameters argc and argv.
Returns a 0.
*/

// Setup some variables.
int done = 0;
char move[4];

int main(int argc, char *argv[])
{
	// Get a random seed.
	srand(time(NULL));

	// Create a game
	GameState *game = createGameState(NULL);

	// Run player vs computer game until done.
	while (done == 0)
	{
		renderBoard(game->board);
		/*printf("%d\n", eval(game ));*/

		// Determine whos turn it is.
		if (game->turn == PLAYER)
		{
			// If it is the players turn, get the desired move.
			printf("%s", "Your move: ");

			// Get the move.
			scanf("%s", move);

			// Check for quit
			if (strncmp(move, "exit", 4) == 0 || strncmp(move, "quit", 4) == 0)
				done = 1;
			else
			{
				if (validMove(move, game->turn, game->board) == 1)
				{
					if (isCheckmate(move, game->turn, game->board) == 1)
					{
						renderBoard(game->board);

						if (game->turn % 2 == 0)
							printf("%s\n", "Player wins.");
						else
							printf("%s\n", "Computer wins.");

						done = 1;
					}
					else
					{
						makeMove(move, game->board);
						game->turn ^= 1;
					}
				}
			}
		}
		else
		{
			// If it is the computers turn, find a move
			findMove(game, move, game->turn^1);
			printf("%s\n", move);

			// Check for checkmate, otherwise make move.
			if (isCheckmate(move, game->turn, game->board) == 1)
			{
				renderBoard(game->board);

				if (game->turn % 2 == 0)
					printf("%s\n", "Player wins.");
				else
					printf("%s\n", "Computer wins.");

				done = 1;
			}
			else
			{
				makeMove(move, game->board);
				game->turn ^= 1;
			}
		}

	}

	freeGameState(game);

	return 0;
}
