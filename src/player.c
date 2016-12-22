#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "piece.h"

Player * createPlayer(int color)
{
	// Allocate mem for player
	Player *new = calloc(1, sizeof(Player));

	// Allocate mem for each piece references
	/*for (int i = 0; i < 16; i++)*/
		/*new->pieces[i] = calloc(1, sizeof(Piece **));*/
	
	new->color = color;
	
	new->kingCastle = false;
	new->queenCastle = false;

	return new;
}

void freePlayer(Player *player)
{
	// Free each of the pieces
	/*for (int i = 0; i < 16; i++)*/
		/*free(*player->pieces[i]);*/

	free(player);
}

// Create a replica of a player
Player * copyPlayer(Player *player)
{
	Player *copy = malloc(sizeof(Player));
	copy->color = player->color;
	copy->kingCastle = player->kingCastle;
	copy->queenCastle = player->queenCastle;
	return copy;
}
