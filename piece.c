#include "piece.h"
#include <stdlib.h>

// Create a piece
Piece * createPiece(unsigned char type, unsigned char color)
{
	Piece *new = malloc(sizeof(Piece));
	new->type = type;
	new->color = color;
	return new;
}

// Function to free a piece
void freePiece(Piece * piece)
{
	free(piece);
}

// Function to covert a piece to a character
char pieceToChar(Piece *piece)
{
	char c;

	switch (piece->type)
	{
		case PAWN: c = 'P'; break;
		case ROOK: c = 'R'; break;
		case KNIGHT: c = 'N'; break;
		case BISHOP: c = 'B'; break;
		case QUEEN: c = 'Q'; break;
		case KING: c = 'K'; break;
		default: c = 0; break;
	}

	// If piece black, covert to lowercase
	if (piece->color == BLACK)
		c += 32;
	
	return c;
}
