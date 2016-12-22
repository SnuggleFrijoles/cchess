#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "piece.h"
#include "player.h"

// Game state
typedef struct GameState {
	
	Board *board;
	Player *white;
	Player *black;
	int turn;

} GameState;

GameState * createGameState();
void freeGameState(GameState *game);

#endif
