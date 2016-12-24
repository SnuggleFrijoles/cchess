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
	piece = NULL;
}

// Create a repilca of a piece
Piece *copyPiece(Piece *piece)
{
	if (piece == NULL)
		return NULL;

	Piece *new = malloc(sizeof(Piece));
	new->type = piece->type;
	new->color = piece->color;
	return new;
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

int pointVal(Piece *piece)
{
	if (piece == NULL)
		return 0;

	switch (piece->type)
	{
		case PAWN: return 1;
		case KNIGHT:
		case BISHOP: return 3;
		case ROOK: return 5;
		case QUEEN: return 9;
		case KING: return 0;
		default: return 0;
	}
}

PiecePos * createPiecePos(unsigned char rank, unsigned char file)
{
	PiecePos *new = malloc(sizeof(PiecePos));
	new->rank = rank;
	new->file = file;
	return new;
}
