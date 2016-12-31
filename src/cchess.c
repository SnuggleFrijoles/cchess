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
#include "move.h"


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
	// Flags
	int simulation = 0;
	int quiet = 0;

	int evalDepth = 3;
	int games = 1;

	// Get a random seed.
	srand(time(NULL));

	// Check for command line flags
	int args = argc - 1;

	while (args > 0)
	{
		if (strncmp(argv[args], "-sim", 4) == 0)
		{
			simulation = 1;
		}
		else if (strncmp(argv[args], "-depth=", 7) == 0)
		{
			if (strlen(argv[args]) >= 8)
			{
				char depthString[2];
				strncpy(depthString, &argv[args][7], 2);
				evalDepth = strtol(depthString, (char **)NULL, 10);
				printf("Setting evaluation depth to %d\n", evalDepth);
			}
		}
		else if (strncmp(argv[args], "-quiet", 6) == 0)
		{
			quiet = 1;
		}
		else if (strncmp(argv[args], "-games=", 7) == 0)
		{
			if (strlen(argv[args]) >= 8)
			{
				char gamesString[3];
				strncpy(gamesString, &argv[args][7], 3);
				games = strtol(gamesString, (char **)NULL, 10);
				printf("Setting number of games to %d\n", games);
			}
		}

		args--;
	}


	// Determine play mode
	if (simulation)
	{
		for (int i = 0; i < games; i++)
		{
			// Create a game
			GameState *game = createGameState(NULL);
			done = 0;

			// Run computer vs computer game until done.
			while (done == 0)
			{
				if (!quiet)
				{
					renderBoard(game->board);
				}

				findMove(game, move, game->turn, evalDepth);

				// Check for checkmate, otherwise make move.
				if (isCheckmate(move, game->turn, game->board) == 1)
				{
					makeMove(move, game->board);

					if (!quiet)
					{
						renderBoard(game->board);
					}

					if (game->turn % 2 == 0)
						printf("%s\n", "Computer 1 wins.");
					else
						printf("%s\n", "Computer 2 wins.");

					done = 1;
				}
				else
				{
					makeMove(move, game->board);
					game->turn ^= 1;
				}
			}

			freeGameState(game);
		}
	}
	else
	{
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
				findMove(game, move, game->turn, evalDepth);
				printf("%s\n", move);

				// Check for checkmate, otherwise make move.
				if (isCheckmate(move, game->turn, game->board) == 1)
				{
					makeMove(move, game->board);
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
	}

	return 0;
}
