#include <stdio.h>		// argc, argv
#include <stdlib.h>		// rand, srand
#include <string.h>		// strncmp
#include <time.h>		// time
#include "cchess.h"
#include "board.h"
#include "piece.h"

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
int turn = 0;
char move[4];
int players;

int main(int argc, char *argv[])
{
	// Get a random seed.
	srand(time(NULL));

	// Create and initialize the board.
	Board *board = createBoard();

	// Determine if 1-player or 2-player game.
	printf("%s", "How many players? (1-2): ");
	scanf("%d", &players);

	// Determine if single player or two player.
	if (players == 2)
	{
		// Run two player game loop until done.
		while (done == 0)
		{
			renderBoard(board);

			// Announce whos move it is.
			if (turn == WHITE)
				printf("%s", "White (uppercase) move: ");
			else
				printf("%s", "Black (lowercase) move: ");

			// Get the move.
			scanf("%s", move);

			if (strncmp(move, "exit", 4) == 0)
				done = 1;
			else
			{
				if (validMove(move, turn, board))
				{
					if (isCheckmate(move, turn, board))
					{
						renderBoard(board);
						if (turn % 2 == 0)
							printf("%s\n", "Capital wins.");
						else
							printf("%s\n", "Lowercase wins.");
						done = 1;
					}
					else
					{
						makeMove(move, board);
						turn = (turn + 1) % 2;
					}
				}
			}
		}
	}
	else if (players == 1)
	{
		// Run player vs computer game until done.
		while (done == 0)
		{
			renderBoard(board);

			// Determine whos turn it is.
			if (turn == PLAYER)
			{
				// If it is the players turn, get the desired move.
				printf("%s", "Your move: ");
				
				// Get the move.
				scanf("%s", move);
			}
			else
			{
				// If it is the computers turn, make a random move.
				// Setup some variables.
				int randMove[4];
				move[0] = '?';

				// Generate random moves until a valid one is found.
				while (validMove(move, turn, board) != 1)
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

				// Check for checkmate, otherwise make move.
				if (isCheckmate(move, turn, board) == 1)
				{
					renderBoard(board);

					if (turn % 2 == 0)
						printf("%s\n", "Player wins.");
					else
						printf("%s\n", "Computer wins.");
					
					done = 1;
				}
				else
				{
					makeMove(move, board);
					turn = (turn + 1) % 2;
				}
			}

			if (strncmp(move, "exit", 4) == 0)
				done = 1;
			else
			{
				if (validMove(move, turn, board) == 1)
				{
					if (isCheckmate(move, turn, board) == 1)
					{
						renderBoard(board);

						if (turn % 2 == 0)
							printf("%s\n", "Player wins.");
						else
							printf("%s\n", "Computer wins.");
						
						done = 1;
					}
					else
					{
						makeMove(move, board);
						turn = (turn + 1) % 2;
					}
				}
			}
		}
	}
	else if (players == 0)
	{
		//render(board);
		int randMove[4];

		int games = 0, cwins = 0, lwins = 0;

		while (games < 10000)
		{
			board = createBoard();
			done = 0;
			// Play two computers against eachother.
			while (done == 0)
			{
				// Setup some variables.
				// Make a random move to start off. Haven't figured out why this is necessary yet
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

				// Generate random moves until a valid one is found.
				while (/*validMove(move, turn, board) != 1*/0)
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

				// Check for checkmate, otherwise make move.
				if (isCheckmate(move, turn, board))
				{
					//render(board);

					if (turn % 2 == 0)
						//printf("%s\n", "Capital wins.");
						cwins++;
					else
						//printf("%s\n", "Lowercase wins.");
						lwins++;
					
					done = 1;
				}
				else
				{
					makeMove(move, board);
					//render(board);
					turn += 1;
				}

				//delay(100);
			}
			games++;
		}

		printf("Capital wins: %d\n", cwins);
		printf("Lowercase wins: %d\n", lwins);
	}

	freeBoard(board);
	
	return 0;
}
