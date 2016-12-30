#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

// Declare board type
typedef struct board {
	// 2D array of double pointers to pieces
	Piece * board[8][8];
} Board;

// Create a board
Board * createBoard();

// Free a board
void freeBoard(Board *board);

Board * copyBoard(Board *board);

// Draw the board
void renderBoard(Board *board);

#endif
