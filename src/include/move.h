/*
 * move.h
 *
 *  Created on: Dec 30, 2016
 *      Author: zach
 */

#ifndef SRC_INCLUDE_MOVE_H_
#define SRC_INCLUDE_MOVE_H_

#include "board.h"
#include "linkedList.h"

// Information about a move
typedef struct move {
	unsigned char startRank;
	unsigned char startFile;
	unsigned char endRank;
	unsigned char endFile;
} Move;

Move * createMove(
		unsigned char startRank,
		unsigned char startFile,
		unsigned char endRank,
		unsigned char endFile
	);

void freeMove(Move *move);

Move * copyMove(Move *orig);

void printMove(Move *move);

void moveToChar(Move *move, char *moveResult);

void makeMove(char *move, Board *board);

void freeMoveList(LinkedList *moves);

#endif /* SRC_INCLUDE_MOVE_H_ */
