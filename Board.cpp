#include "Board.h"
#include "SDL.h"
#include "Window.h"
#include "Box.h"
#include "GridPiece.h"
#include <iostream>

int Board::xPos = 0;
int Board::yPos = 0;
int Board::rows = 0;
int Board::cols = 0;
SDL_Color Board::gridColor;

void Board::render() {
	renderBoard();
	highlightPiece->render();
	movePiece->render();
	holder.render();
	nextHolder.render();
	renderGrid();
}

void Board::attemptLeftMove() {
	
	if (canMoveLeft()) {
		movePiece->moveLeft();
		updateHighlightLocation();
	}
}

void Board::attemptRightMove() {
	
	if (canMoveRight()) {
		movePiece->moveRight();
		updateHighlightLocation();
	}
}

void Board::attemptDownMove() {

	if (canMoveDown()) {
		lastUpdated = SDL_GetTicks();
		movePiece->moveDown();
	}
}
void Board::swapHeld() {
	char newPiece = holder.swapHeldPiece(movePiece->getType());
	if (newPiece != ' ') {
		movePiece->reset(newPiece);
	}
	else {
		movePiece->reset(nextHolder.getNextPiece());
	}
	updateHiglightPiece();
	updateHighlightLocation();
}

void Board::renderGrid() {
	SDL_Rect gridRect;
	SDL_SetRenderDrawColor(Window::renderer, gridColor.r, gridColor.g, gridColor.b, 255);
	gridRect.w = Box::boxWidth;
	
	gridRect.h = Box::boxHeight;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gridRect.x = xPos + j * Box::boxWidth;
			gridRect.y = yPos + i * Box::boxHeight;
			SDL_RenderDrawRect(Window::renderer, &gridRect);
		}
	}

}

void Board::renderBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].render();
		}
	}
}


void Board::init(int windowHeight, int windowWidth, int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	initializeColors();
		//board takes up at most 90 percent of screen height, can perhaps change letter.
	int maxBoardHeight = windowHeight * .9;
	int maxBoxHeight = maxBoardHeight / rows;
	int boardHeight = maxBoxHeight * rows;
	//for now the height and width of the boxes will alwayhs be the same.
	Box::boxHeight = maxBoxHeight;
	Box::boxWidth = maxBoxHeight;
	yPos = windowHeight - boardHeight;
	int boardWidth = Box::boxWidth * cols;
	int horizontalSpace = windowWidth - boardWidth;
	xPos = horizontalSpace / 2;
	board = new Box * [rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].init(i, j);

		}
	}
	nextHolder.init(xPos + boardWidth + Box::boxWidth, yPos);


	holder.setY(yPos);
	holder.init();
	movePiece = new Piece();
	highlightPiece = new Piece();
	movePiece->reset(nextHolder.getNextPiece());
	updateHiglightPiece();
	updateHighlightLocation();
	lastUpdated = SDL_GetTicks();



	
	
	
}

void Board::plummet() {
	movePiece->setBoxes(highlightPiece->getBoxes());
	spawnNewPiece();
	
}



void Board::updateHiglightPiece() {
	SDL_Color tempColor = movePiece->getSDLColor();
	tempColor.a = 122;
	highlightPiece->setColor(tempColor, movePiece->getColor());
	highlightPiece->setBoxes(movePiece->getBoxes());
}

void Board::updateHighlightLocation() {
	highlightPiece->setBoxes(movePiece->getBoxes());
	boxLocation tempBoxes[4];
	boxLocation* currentBoxes = highlightPiece->getBoxes();
	for (int i = 0; i < 4; i++) {
		tempBoxes[i].row = currentBoxes[i].row;
		tempBoxes[i].col = currentBoxes[i].col;
	}
	bool done = false;
	while (!done) {
		
		for (int i = 0; i < 4; i++) {
			if (tempBoxes[i].row + 1 >= rows) {
				done = true;
				break;
			}
			if (board[tempBoxes[i].row+1][tempBoxes[i].col].isEmpty()) {
				continue;
			}
			else {
				done = true;
				break;
			}
		}
		if (!done) {
			for (int i = 0; i < 4; i++) {	//incremenmting
				tempBoxes[i].row++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {	//assigning after done.
		currentBoxes[i].row = tempBoxes[i].row;
		currentBoxes[i].col = tempBoxes[i].col;
	}



}




void Board::spawnNewPiece() {
	
	boxLocation* boxes = movePiece->getBoxes();
	for (int i = 0; i < 4; i++) {
		board[boxes[i].row][boxes[i].col].updateColor(movePiece->getColor());
		board[boxes[i].row][boxes[i].col].updateType('f');
	}
	movePiece->reset(nextHolder.getNextPiece());
	
	while (true) {
		int row = checkForRows();
		if (row == -1) {
			break;
		}
		else {
			removeRow(row);
		}
	}
	updateHiglightPiece();		//updates the color of the highlight piece, as well as initial position.
	updateHighlightLocation();
	checkLevel();
}



Board::Board() {
	timeToMove = 1000;	//one second in between updates;
	score = 0;
	level = 0;
	rowsRemoved = 0;
	boardReset = false;
}


void Board::checkLevel() {
	level = totalRowsCleared % 10;
	timeToMove = 1000 - (50 * level);
	if (timeToMove <= 0) {
		timeToMove = 100;
	}


}
void Board::update() {
	if (boardReset) {
		boardReset = false;
	}
	if (SDL_GetTicks() - lastUpdated >= timeToMove) {
		if (canMoveDown()) {
			movePiece->update();
			canRotateClockwise();
		}
		else {
			if (checkIfGameOver()) {
				SDL_Delay(2000);
				resetBoard();
				return;
			}
			spawnNewPiece();
		}
			lastUpdated = SDL_GetTicks();
	}
	if (!(canMoveDown() || canMoveLeft() || canMoveRight() || canRotateClockwise())) {
		if (checkIfGameOver()) {
			SDL_Delay(2000);
			resetBoard();
			return;
		}
		spawnNewPiece();
		lastUpdated = SDL_GetTicks();
	}
}

bool Board::checkIfGameOver() {
	for (int i = 0; i < 4; i++) {
		if (!(board[movePiece->getBoxes()[i].row][movePiece->getBoxes()[i].col].isEmpty())) {
			
			SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
			SDL_RenderClear(Window::renderer);
			holder.render();
			nextHolder.render();
			renderBoard();
			renderGrid();
			SDL_RenderPresent(Window::renderer);
			
			
			
			return true;
		}
	}
	return false;
}


Board::~Board() {
	for (int i = 0; i < rows; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete movePiece;
	delete highlightPiece;
}

bool Board::canMoveDown() {
	boxLocation* boxes = movePiece->getBoxes();
	for (int i = 0; i < 4; i++) {
		if (boxes[i].row + 1 >= rows) {
			return false;
		}
		else if (!(board[boxes[i].row + 1][boxes[i].col].isEmpty())) {	//if the square below isn't empty
			return false;
		}
	}
	return true;
}
bool Board::canMoveRight() {
	bool canMoveRight = true;
	boxLocation* pieceBoxes = movePiece->getBoxes();
	int pieceRow, pieceCol, checkRow, checkCol;
	for (int i = 0; i < 4; i++) {
		pieceRow = pieceBoxes[i].row;
		pieceCol = pieceBoxes[i].col;
		checkRow = pieceRow;
		checkCol = pieceCol + 1;
		if (checkCol >= cols) {
			canMoveRight = false;
			return false;
		}

		else {
			if (board[checkRow][checkCol].isEmpty()) {
				continue;
			}
			else {
				canMoveRight = false;
				return false;
			}
		}

	}
	return true;
}

bool Board::canMoveLeft() {
	bool canMoveLeft = true;
	boxLocation* pieceBoxes = movePiece->getBoxes();
	int pieceRow, pieceCol, checkRow, checkCol;
	for (int i = 0; i < 4; i++) {
		pieceRow = pieceBoxes[i].row;
		pieceCol = pieceBoxes[i].col;
		checkRow = pieceRow;
		checkCol = pieceCol - 1;
		if (pieceCol < 0) {
			canMoveLeft = false;
			return false;
		}
		else {
			if (board[checkRow][checkCol].isEmpty()) {
				continue;
			}
			else {
				canMoveLeft = false;
				return false;
			}
		}

	}
	return true;
}

void Board::initializeColors() {
	Box::blue.r = Box::blue.g = 0;
	Box::blue.b = 240;
	Box::blue.a = 255;
	


	Box::teal.r = 0;
	Box::teal.g = Box::teal.b = 240;
	Box::teal.a = 255;

	Box::green.r = Box::green.b = 0;
	Box::green.g = 240;
	Box::green.a = 255;

	Box::purple.r = 160;
	Box::purple.g = 0;
	Box::purple.b = 240;
	Box::purple.a = 255;

	Box::red.r = 240;
	Box::red.g = Box::red.b = 0;
	Box::red.a = 255;

	Box::yellow.r = Box::yellow.g = 240;
	Box::yellow.b = 0;
	Box::yellow.a = 255;

	Box::orange.r = 240;
	Box::orange.g = 160;
	Box::orange.b = 0;
	Box::orange.a = 255;

	gridColor.r = gridColor.b = gridColor.g = 29;
	gridColor.a = 255;
}


int Board::checkForRows() {
	bool rowFull = true;
	for (int i = rows - 1; i >= 0; i--) {
		rowFull = true;
		for (int j = 0; j < cols; j++) {
			if (board[i][j].isEmpty()) {
				rowFull = false;
			}
		}
		if (rowFull == true) {
			rowsRemoved++;
			totalRowsCleared++;
			return i;
		}
	}

	
	updateScore();
	
	return -1;
}

bool Board::justReset() {
	return boardReset;
}
void Board::resetBoard() {
	score = 0;
	level = 0;
	rowsRemoved = 0;
	totalRowsCleared = 0;
	clearBoard();
	nextHolder.resetPieces();
	holder.clear();
	movePiece->reset(' ');
	updateHiglightPiece();		//updates the color of the highlight piece, as well as initial position.
	updateHighlightLocation();
	lastUpdated = SDL_GetTicks();
	boardReset = true;
	timeToMove = 1000;

}
void Board::clearBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].updateType('e');

		}
	}
}


void Board::updateScore() {

	switch (rowsRemoved) {
	case 0:
		break;
	case 1:
		score += 40 * (level + 1);
		break;
	case 2:
		score += 100 * (level + 1);
		break;
	case 3:
		score += 300 * (level + 1);
		break;
	case 4:
		score += 1200 * (level + 1);
		break;
	default:
		std::cout << "how did you remove 5 rows" << std::endl;
		break;
	}
	rowsRemoved = 0;
	
}
void Board::removeRow(int newRow) {
	
	for (int i = 0; i < cols; i++) {
		board[newRow][i].updateType('e');
	}
	SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Window::renderer);
	render();
	SDL_RenderPresent(Window::renderer);
	SDL_Delay(50);
	bool done = false;
	int lookingAtRow = newRow - 1;
	while (lookingAtRow >= 0) {
		for (int i = 0; i < cols; i++) {
			if (!(board[lookingAtRow][i].isEmpty())) {
				
				board[lookingAtRow + 1][i].updateType('f');
				board[lookingAtRow + 1][i].updateColor(board[lookingAtRow][i].getColor());
				board[lookingAtRow][i].updateType('e');
				
				
			}
		}

		lookingAtRow--;
	}
	

}

void Board::printBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << board[i][j].getType() << " ";
		}
		std::cout<< std::endl;
	}
	std::cout << std::endl;
}


bool Board::canRotateClockwise() {
	boxLocation newLocation[4];
	GridPiece** grid;
	boxLocation* topLeftCorner;
	int topLeftRow, topLeftCol;
	switch (movePiece->getType()) {
	case 'I':
		grid = makeClockwiseGrid(4, 4);
		topLeftCorner = movePiece->getTopLeft();
		topLeftRow = topLeftCorner->row;
		topLeftCol = topLeftCorner->col;
		if (checkIfCanRotate(grid, 4, 4, topLeftRow, topLeftCol)) {
		
			deleteGrid(grid, 4);
			return true;
		}
		deleteGrid(grid, 4);
		//implement I piece here, because it's a 4x4 grid.
		break;
	case 'O':
		break;
	default:
		 grid = makeClockwiseGrid(3,3);
		topLeftCorner = movePiece->getTopLeft();
		topLeftRow = topLeftCorner->row;
		topLeftCol = topLeftCorner->col - 1;
		if (checkIfCanRotate(grid, 3, 3, topLeftRow, topLeftCol)) {
		
			deleteGrid(grid, 3);
			return true;
		}
		deleteGrid(grid, 3);
		
		break;
	}
	return false;
}
//returns the new grid that a piece rotated clockwise would use.
GridPiece** Board::makeClockwiseGrid(int gridRows, int gridCols) {
	GridPiece** grid;
	grid = new GridPiece * [gridRows];
	for (int i = 0; i < gridRows; i++) {
		grid[i] = new GridPiece[gridCols];
	}

	boxLocation* topLeftCorner = movePiece->getTopLeft();
	int topLeftRow, topLeftCol;
	
	
	topLeftRow = topLeftCorner->row;
	topLeftCol = topLeftCorner->col;
	
	
	boxLocation* boxes = movePiece->getBoxes();	//piece boxes

	for (int i = 0; i < gridRows; i++) {
		for (int j = 0; j < gridCols; j++) {
			grid[i][j].row = topLeftRow + i;
			grid[i][j].col = topLeftCol + j;
			for (int k = 0; k < 4; k++) {	//check as compared to the boxes.
				if (boxes[k].row == topLeftRow + i && boxes[k].col == topLeftCol + j) {	//tests if the piece is there.
					grid[i][j].isEmpty = false;
					break;
				}
				else {
					grid[i][j].isEmpty = true;
				}
			}
		}
	}
	
	transpose(grid, gridRows, gridCols);	//how to rotate 90 degrees, transpose then reverse rows.
	reverseRows(grid, gridRows, gridCols);
	
	for (int i = 0; i < gridRows; i++) {
		for (int j = 0; j < gridCols; j++) {
			if (!(grid[i][j].isEmpty)) {	//update the row and col accordingly
				grid[i][j].row = topLeftRow + i;
				grid[i][j].col = topLeftCol + j;
			}
			
		}
	}

	return grid;
}


void Board::attemptRotateClockwise() {
	if (canRotateClockwise()) {
		if (movePiece->getType() == 'I') {
			rotateClockwise(4, 4);	
		}
		else {
			rotateClockwise(3, 3);
		}
		updateHighlightLocation();
	}
}

void Board::rotateClockwise(int rows, int cols) {
	GridPiece** grid = makeClockwiseGrid(rows,cols);
	boxLocation* boxes = movePiece->getBoxes();
	int numPiece = 0;	//the piece block we're updating currently
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!(grid[i][j].isEmpty)) {
				
				boxes[numPiece].row = grid[i][j].row;
				boxes[numPiece].col = grid[i][j].col;
				
				numPiece++;
				
			}
		}
	}
	deleteGrid(grid, rows);

}

bool Board::checkIfCanRotate(GridPiece** grid, int rows, int cols, int topLeftRow, int topLeftCol) {
	bool canRotate = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j].isEmpty) {
				continue;
			}
			else {
				if (grid[i][j].row >= this->rows || grid[i][j].row < 0 || grid[i][j].col >= this->cols || grid[i][j].col < 0) {	//if the col goes off the screen
					
					return false;
				}
				else {
					if (board[grid[i][j].row][grid[i][j].col].isEmpty()) {
						continue;
					}
					else {
						
						return false;
					}
				}
			}
		}
	}
	return true;
}



void Board::transpose(GridPiece** grid, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < i; j++) {
			swap(grid, i, j, j, i);
		}
	}
}
void Board::reverseRows(GridPiece** grid, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		int start = 0;
		int end = cols - 1;
		while (start < end) {
			swap(grid, i, start, i, end);
			start++;
			end--;
		}
	}
}

void Board::swap(GridPiece** grid, int row1, int col1, int row2, int col2) {
	GridPiece tempPiece;
	tempPiece.row = grid[row1][col1].row;
	tempPiece.col = grid[row1][col1].col;
	
	tempPiece.isEmpty = grid[row1][col1].isEmpty;


	grid[row1][col1].row = grid[row2][col2].row;
	grid[row1][col1].col = grid[row2][col2].col;

	grid[row1][col1].isEmpty = grid[row2][col2].isEmpty;

	grid[row2][col2].row = tempPiece.row;
	grid[row2][col2].col = tempPiece.col;

	grid[row2][col2].isEmpty = tempPiece.isEmpty;
}



void Board::printGrid(GridPiece** grid,int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j].isEmpty) {
				std::cout << "e" << " ";
			}
			else {
				std::cout << "f" << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
void Board::deleteGrid(GridPiece** grid, int cols) {
	for (int i = 0; i < cols; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}