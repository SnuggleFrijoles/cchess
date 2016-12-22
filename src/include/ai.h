#ifndef AI_H
#define AI_H

#include "gameState.h"
#include "linkedList.h"

int eval(GameState *game, int depth);

void findMove(GameState *game, char move[4], int turn);

LinkedList * findPieces(GameState *game, int turn);

LinkedList * findMoves(GameState *game, PiecePos *piecePos);

#endif
