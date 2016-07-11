#ifndef CCHESS_H
#define CCHESS_H

#include "board.h"

#define PLAYER 0
#define COMPUTER 0

// Valid move functions
int validMove(char move[4], int turn, Board *board);
int validPawn(char move[4], int turn, Board *board);
int validRook(char move[4], int turn, Board *board);
int validKnight(char move[4], int turn, Board *board);
int validBishop(char move[4], int turn, Board *board);
int validQueen(char move[4], int turn, Board *board);
int validKing(char move[4], int turn, Board *board);

#endif
