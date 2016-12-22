#ifndef VALID_H
#define VALID_H

// Valid move functions
int validMove(char move[4], int turn, Board *board);
int validPawn(char move[4], int turn, Board *board);
int validRook(char move[4], int turn, Board *board);
int validKnight(char move[4], int turn, Board *board);
int validBishop(char move[4], int turn, Board *board);
int validQueen(char move[4], int turn, Board *board);
int validKing(char move[4], int turn, Board *board);

void moveToChar(Move *move, char *moveResult);

#endif
