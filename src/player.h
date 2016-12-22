#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "piece.h"

typedef struct Player {

	unsigned char color;

	// Array of double pointers to pieces
	//Piece ** pieces[16];

	// State variables
	bool kingCastle;
	bool queenCastle;

} Player;

Player * createPlayer(int color);
void freePlayer(Player *player);
Player * copyPlayer(Player *player);

#endif
