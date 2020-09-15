#pragma once
#include "Box.h"
#include "GridPiece.h"
#include "Piece.h"
#include "HoldRectangle.h"
#include "nextShapesHolder.h"
class Board
{

public:
	void printGrid(GridPiece**,int,int);
	void deleteGrid(GridPiece**, int);
	void transpose(GridPiece**, int, int);
	void swap(GridPiece**, int, int, int, int);
	void reverseRows(GridPiece**, int, int);
	bool checkIfCanRotate(GridPiece**, int, int, int, int);
	GridPiece** makeClockwiseGrid(int,int);

	void render();
	void update();
	void renderGrid();
	void renderBoard();
	void attemptLeftMove();
	void attemptRightMove();
	void attemptDownMove();
	void attemptRotateClockwise();
	void rotateClockwise(int,int);

	void plummet();

	void swapHeld();

	bool canMoveRight();
	bool canMoveLeft();
	bool canMoveDown();
	bool canRotateClockwise();



	void printBoard();
	void spawnNewPiece();
	void updateHiglightPiece();
	void updateHighlightLocation();


	void updateScore();

	void resetBoard();
	void clearBoard();
	bool justReset();
	void init(int windowHeight, int windowWidth, int rows, int cols);


	void checkLevel();

	int checkForRows();	//returns -1 if there isn't one to return, returns the row otherwise.
	void removeRow(int row);
	bool checkIfGameOver();
	Board();
	~Board();
	static int xPos;
	static int yPos;
	void initializeColors();
	static int rows;
	static int cols;
	static SDL_Color gridColor;
private:
	Uint32 lastUpdated;
	int timeToMove;
	Piece* movePiece;
	Piece* highlightPiece;
	Box** board;
	HoldRectangle holder;
	nextShapesHolder nextHolder;
	int score;
	int level;
	int rowsRemoved;
	int totalRowsCleared;
	bool boardReset;
};

