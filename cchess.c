#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Function: createBoard
	Sets up the board for the game by creating a 2d array and populating it with the positon of each piece.
	Takes no parameters.
	Returns a double pointer to the 2d character array.
*/

char ** createBoard()
{
	int height = 9;
	int width = 9;

	// Create and allocate the heap memory required for each row of the array.
	char **board;
	board = (char **)malloc(height * sizeof(int *));

	// Allocate memory for each column in the 2d array.
	for (int i = 0; i < height; ++i)
		board[i] = (char *)malloc(width * sizeof(int));

	// Setup the algebraic notation.
	for (int i = 1; i < 9; ++i)
		board[0][i] = 96 + i;

	for (int i = 1; i < 9; ++i)
		board[i][0] = 57 - i;

	// Populate the board with the starting positions of each piece.
	// Pawns
	for (int i = 1; i < 9; ++i)
	{
		board[2][i] = 'p';
		board[7][i] = 'P';
	}
	// Rooks
	board[1][1] = 'r';
	board[1][8] = 'r';
	board[8][1] = 'R';
	board[8][8] = 'R';
	// Knights
	board[1][2] = 'k';
	board[1][7] = 'k';
	board[8][2] = 'K';
	board[8][7] = 'K';
	// Bishops
	board[1][3] = 'b';
	board[1][6] = 'b';
	board[8][3] = 'B';
	board[8][6] = 'B';
	// Queens
	board[1][4] = 'q';
	board[8][5] = 'Q';
	// Kings
	board[1][5] = 'x';
	board[8][4] = 'X';

	return board;
}

/*
	Function: render
	Prints the board in a easy to understand manner.
	Takes a double pointer to the char array.
	Returns nothing.
*/

void render(char **board)
{
	// Clears the screen.
	system("clear");

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			char c = board[i][j];

			if (c == 0)
				printf("%s", " ");
			else
				printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

/*
	Function: freeBoard
	Free the heap memory associated with the board.
	Takes parameter double pointer to the board.
	Returns nothing.
*/

void freeBoard(char **board)
{
	// First free the memory associated with each array within the large array.
	for (int i = 0; i < 9; i++)
	{
		free(board[i]);
	}

	// Then free the memory from the mother array.
	free(board);
}

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
	printf("%d %d %d\n", piece, turn, turn % 2);

	// Check to see if the selected position and move to position are valid.
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
			if (endy - starty == 2 && starty == 2 && board[3][startx] == 0)
				return 1;
			// Allow standard one space forward move.
			else if (endy - starty == 1 && endx - startx == 0)
				return 1;
			else
				return 0;
		}
	}
	if (piece == 'P')
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
			if (endy - starty == -2 && starty == 7 && board[6][startx] == 0)
				return 1;
			// Allow standard one space forward move.
			else if (endy - starty == -1 && endx - startx == 0)
				return 1;
			else
				return 0;
		}
	}

	// Check to see if move is valid for rook.

	return 1;
}

/*
	Function: makeMove
	Conducts a valid move.
	Takes parameters string of move and double pointer to the board.
	Returns nothing.
*/

void makeMove(char *move, char **board)
{
	// Get the integer values for the move.
	int startx = move[0] - 96;
	int starty = 9 - (move[1] - 48);
	int endx = move[2] - 96;
	int endy = 9 - (move[3] - 48);
	
	// Conduct the move.
	board[endy][endx] = board[starty][startx];
	board[starty][startx] = 0;
}

/*
	Function: main
	Runs the game then frees all memory.
	Takes standard parameters argc and argv.
	Returns a 0.
*/

// Setup some variables.
int done = 0;
int turn = 0;
char move[4];

int main(int argc, char *argv[])
{
	// Initialize the board.
	char **board = createBoard();

	// Run the main game loop until the game is done.
	while (done == 0)
	{
		render(board);

		// Announce whos move it is.
		if (turn % 2 == 0)
			printf("%s", "Capital move: ");
		else
			printf("%s", "Lowercase move: ");

		// Get the move.
		scanf("%s", move);

		if (strncmp(move, "exit", 4) == 0)
			done = 1;
		else
		{
			if (validMove(move, turn, board) == 1)
			{
				makeMove(move, board);
				turn += 1;
			}
		}
	}

	freeBoard(board);

	return 0;
}