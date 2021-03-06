#ifndef PIECES_H
#define PIECES_H

#include "linkedList.h"

// Give each piece a value
#define PAWN 0
#define ROOK 1
#define KNIGHT 2
#define BISHOP 3
#define QUEEN 4
#define KING 5

// Define piece colors
#define WHITE 0
#define BLACK 1

// Define piece type
typedef struct piece {
	unsigned char type;
	unsigned char color;
} Piece;

// Declare createPiece function
Piece * createPiece(unsigned char type, unsigned char color);

// Function to free a piece
void freePiece(Piece * piece);

Piece *copyPiece(Piece *piece);

// Function to covert piece to character
char pieceToChar(Piece *piece);

// Function to get the point value of a piece
int pointVal(Piece *piece);

// Piece position structure
typedef struct piecePos {
	unsigned char rank;
	unsigned char file;
} PiecePos;

PiecePos * createPiecePos(unsigned char rank, unsigned char file);

void freePiecePos(PiecePos *p);

void freePiecePosList(LinkedList *piecePos);

#endif
