
/*
	Function: validMove
	Determines if a move is valid.
	Takes parameter string of move.
	Returns either a 1 or 0 depending of if the move is valid.
*/

int validMove(char *move, int turn, char **board)
{
	// Get the integer values for the move.
	int startx = move[0] - 96;
	int starty = 9 - (move[1] - 48);
	int endx = move[2] - 96;
	int endy = 9 - (move[3] - 48);


	// Get the piece being moved.
	char piece = board[starty][startx];

	// Check to see if the start and end positions are valid.
	if (startx < 1 | startx > 8)
		return 0;
	if (starty < 1 | starty > 8)
		return 0;
	if (endx < 1 | endx > 8)
		return 0;
	if (endy < 1 | endy > 8)
		return 0;

	// Check to see if the wrongly owned piece is being moved.
	if (turn % 2 == 0 && (piece < 65 | piece > 90))
		return 0;
	if (turn % 2 == 1 && (piece < 97 | piece > 122))
		return 0;

	// Don't allow friendly fire.
	if (board[starty][startx] >= 65 && board[starty][startx] <= 90 && board[endy][endx] >= 65 && board[endy][endx] <= 90)
		return 0;
	if (board[starty][startx] >= 97 && board[starty][startx] <= 122 && board[endy][endx] >= 97 && board[endy][endx] <= 122)
		return 0;

	// Check if move is valid for a pawn.
	if (piece == 'p')
	{
		// Check to see if attacking.
		if (board[endy][endx] >= 65 && board[endy][endx] <= 90)
		{
			// Only allow diagonal attacks.
			if (endy - starty == 1 && (endx - startx == 1 | endx - startx == -1))
				return 1;
			else
				return 0;
		}
		else
		{
			// Allow two space move from starting position if nothing in the way.
			if (endy - starty == 2 && starty == 2 && board[3][startx] == 0 && endx - startx == 0)
				return 1;
			// Allow standard one space forward move.
			else if (endy - starty == 1 && endx - startx == 0)
				return 1;
			else
				return 0;
		}
	}
	else if (piece == 'P')
	{
		// Check to see if attacking.
		if (board[endy][endx] >= 97 && board[endy][endx] <= 122)
		{
			// Only allow diagonal attacks.
			if (endy - starty == -1 && (endx - startx == 1 | endx - startx == -1))
				return 1;
			else
				return 0;
		}
		else
		{
			// Allow two space move from starting position if nothing in the way.
			if (endy - starty == -2 && starty == 7 && board[6][startx] == 0 && endx - startx == 0)
				return 1;
			// Allow standard one space forward move.
			else if (endy - starty == -1 && endx - startx == 0)
				return 1;
			else
				return 0;
		}
	}

	// Check to see if move is valid for rook.
	else if (piece == 'r' | piece == 'R')
	{
		// Rooks must move horizontally
		if (endy - starty == 0)
		{
			// Check to make sure there are no pieces in between the start and end positions.
			if (endx > startx)
			{
				for (int i = startx + 1; i < endx; i++)
				{
					if (board[starty][i] != 0)
						return 0;
				}
				return 1;
			}
			else
			{
				for (int i = startx - 1; i > endx; i--)
				{
					if (board[starty][i] != 0)
						return 0;
				}
				return 1;
			}
		}
		// or vertically.
		else if (endx - startx == 0)
		{
			// Check to make sure there are no pieces in between the start and end positions.
			if (endy > starty)
			{
				for (int i = starty + 1; i < endy; i++)
				{
					if (board[i][startx] != 0)
						return 0;
				}
				return 1;
			}
			else
			{
				for (int i = starty - 1; i > endy; i--)
				{
					if (board[i][startx] != 0)
						return 0;
				}
				return 1;
			}
		}
		else
			return 0;
	}

	// Check to see if move is valid for a knight.
	else if (piece == 'k' | piece == 'K')
	{
		// Only allow proper knight moves.
		if (endy - starty == 1 && endx - startx == 2)
			return 1;
		else if (endy - starty == 1 && endx - startx == -2)
			return 1;
		else if (endy - starty == -1 && endx - startx == 2)
			return 1;
		else if (endy - starty == -1 && endx - startx == -2)
			return 1;
		else if (endy - starty == 2 && endx - startx == 1)
			return 1;
		else if (endy - starty == 2 && endx - startx == -1)
			return 1;
		else if (endy - starty == -2 && endx - startx == 1)
			return 1;
		else if (endy - starty == -2 && endx - startx == -1)
			return 1;
		else
			return 0;
	}

	// Check to see if move is valid for a bishop.
	else if (piece == 'b' | piece == 'B')
	{
		// Only allow diagonal moves.
		if (endx - startx == endy - starty | endx - startx == -(endy - starty))
		{
			// Get the direction of the move.
			int xdir = endx - startx;
			int ydir = endy - starty;

			// Make sure no pieces are in the way.
			if (xdir > 0 && ydir > 0)
			{
				for (int i = 1; i < endx - startx; ++i)
				{
					if (board[starty+i][startx+i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir > 0 && ydir < 0)
			{
				for (int i = 1; i < endx - startx; ++i)
				{
					if (board[starty-i][startx+i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir < 0 && ydir > 0)
			{
				for (int i = 1; i < -(endx - startx); ++i)
				{
					if (board[starty+i][startx-i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir < 0 && ydir < 0)
			{
				for (int i = 1; i < -(endx - startx); ++i)
				{
					if (board[starty-i][startx-i] != 0)
						return 0;
				}
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}

	// Check to see if a move is valid for a queen.
	else if (piece == 'q' | piece == 'Q')
	{
		// Allow diagonal moves.
		if (endx - startx == endy - starty | endx - startx == -(endy - starty))
		{
			// Get the direction of the move.
			int xdir = endx - startx;
			int ydir = endy - starty;

			// Make sure no pieces are in the way.
			if (xdir > 0 && ydir > 0)
			{
				for (int i = 1; i < endx - startx; ++i)
				{
					if (board[starty+i][startx+i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir > 0 && ydir < 0)
			{
				for (int i = 1; i < endx - startx; ++i)
				{
					if (board[starty-i][startx+i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir < 0 && ydir > 0)
			{
				for (int i = 1; i < -(endx - startx); ++i)
				{
					if (board[starty+i][startx-i] != 0)
						return 0;
				}
				return 1;
			}
			else if (xdir < 0 && ydir < 0)
			{
				for (int i = 1; i < -(endx - startx); ++i)
				{
					if (board[starty-i][startx-i] != 0)
						return 0;
				}
				return 1;
			}
			else
				return 0;
		}
		// or horizontal moves.
		else if (endy - starty == 0)
		{
			// Check to make sure there are no pieces in between the start and end positions.
			if (endx > startx)
			{
				for (int i = startx + 1; i < endx; i++)
				{
					if (board[starty][i] != 0)
						return 0;
				}
				return 1;
			}
			else
			{
				for (int i = startx - 1; i > endx; i--)
				{
					if (board[starty][i] != 0)
						return 0;
				}
				return 1;
			}
		}
		// or vertically.
		else if (endx - startx == 0)
		{
			// Check to make sure there are no pieces in between the start and end positions.
			if (endy > starty)
			{
				for (int i = starty + 1; i < endy; i++)
				{
					if (board[i][startx] != 0)
						return 0;
				}
				return 1;
			}
			else
			{
				for (int i = starty - 1; i > endy; i--)
				{
					if (board[i][startx] != 0)
						return 0;
				}
				return 1;
			}
		}
		else
			return 0;
	}

	// Check to see if move is valid for a king.
	else if (piece == 'x' | piece == 'X')
	{
		if (endx - startx > 1 | endx - startx < -1)
			return 0;
		else if (endy - starty > 1 | endy - starty < -1)
			return 0;
		else
			return 1;
	}

	return 1;
}
