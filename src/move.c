/*
 * move.c
 *
 *  Created on: Dec 30, 2016
 *      Author: zach
 */

#include <stdlib.h>
#include <stdio.h>

#include "move.h"
#include "board.h"

Move * createMove(
		unsigned char startRank,
		unsigned char startFile,
		unsigned char endRank,
		unsigned char endFile
	)
{
	Move *new = malloc(sizeof(Move));

	new->startRank = startRank;
	new->startFile = startFile;
	new->endRank = endRank;
	new->endFile = endFile;

	return new;
}

void freeMove(Move *move)
{
	free(move);
}

Move * copyMove(Move *orig)
{
	Move *copy = createMove(orig->startRank, orig->startFile, orig->endRank, orig->endFile);
	return copy;
}

void printMove(Move *move)
{
	printf("%d %d %d %d\n", move->startRank, move->startFile, move->endRank, move->endFile);
}

void moveToChar(Move *move, char moveResult[4])
{
	moveResult[0] = 'a' + move->startFile;
	moveResult[1] = '8' - move->startRank;
	moveResult[2] = 'a' + move->endFile;
	moveResult[3] = '8' - move->endRank;
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
