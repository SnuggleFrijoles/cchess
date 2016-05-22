#ifndef PIECES_H
#define PIECES_H

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

// Function to covert piece to character
char pieceToChar(Piece *piece);

#endif
