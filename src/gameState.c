#include <stdlib.h>
#include <stdio.h>

#include "gameState.h"
#include "player.h"

GameState * createGameState(GameState *copy)
{
	// Allocate mem for GameState
	GameState *new = calloc(1, sizeof(GameState));

	// Copy previous state
	if (copy != NULL)
	{
		new->board = copyBoard(copy->board);	
		new->white = copyPlayer(copy->white);
		new->black = copyPlayer(copy->black);
		new->turn = copy->turn;
		return new;
	}

	// Allocate mem for Board
	new->board = createBoard();

	// Allocate mem for players
	new->white = createPlayer(WHITE);
	new->black = createPlayer(BLACK);

	// White starts
	new->turn = WHITE;

	// Assign player pieces to those on the board
	/*for (int i = 0; i < 2; i++)*/
	/*{*/
		/*for (int j = 0; j < 8; j++)*/
		/*{*/
			/*new->white->pieces[8*i+j] = new->board->boardRefs[7-i][j];*/
			/*new->black->pieces[8*i+j] = new->board->boardRefs[i][j];*/
		/*}*/
	/*}*/


	return new;
}

void freeGameState(GameState *game)
{
	// Free the board
	freeBoard(game->board);

	// Free players
	freePlayer(game->white);
	freePlayer(game->black);

	// Free game state
	free(game);
}
