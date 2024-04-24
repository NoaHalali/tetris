#include "player.h"

//This function is initializing the board for each player
player::player(int minX, int color, int playerNumber)
{
	this->clearBoard();
	this->color = color;
	this->minX = minX;
	this->playerNum = playerNumber;
	this->drawBorder();
	currMove = 0;
	this->didLose = false;
}

//This function is for drawing both players boards
void player::drawBorder() const
{
	
	for (int col = minX; col < minX + player::GAME_WIDTH; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, player::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::MIN_Y + player::GAME_HEIGHT; row++)
	{
		gotoxy(minX - 1, row);
		cout << "|";

		gotoxy(player::GAME_WIDTH + minX, row);
		cout << "|";
	}
}

//This function gets a shape, checks if its possible to move it down on the screen and on the matrix and if so it moves it
bool player::checkAndMovePieceDown()
{
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);			//Delete shape from screen
	deletePieceOnBoard(currShape);																	//Delete shape from matrix
	bool isShapeCanMove = true;
	shape tempShapeDown = currShape;																//Temp shape to check if shape can move
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)													//Moving the temp shape 
	{
		tempShapeDown.getShape()[i].movePointDown();
	}
	if (checkMovePieceDown(tempShapeDown))															//Checking if temp shape is in an approved place if so we move the curr shape
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)												//Moving curr shape
		{
			currShape.getShape()[i].movePointDown();
		}
		placePieceOnBoard(currShape);																//Putting shape in the matrix
		currShape.drawShape('#', color, minX);														//Drawing the shape on screen
		Sleep(GameConfig::AVG_SLEEP);

	}
	else
	{
		currShape.drawShape('#', color, minX);														//Keep the shape where it was before trying to move
		placePieceOnBoard(currShape);																//Putting shape in the matrix
		isShapeCanMove = false;																		//Cant move anymore
		checkAndRemoveFullLinesOnBoard();															//checking if line is full to delete
		if (checkIfDidLose() == TRUE)																//Checking if one player got to the last line
			didLose = true;
	}
	return isShapeCanMove;
}

//This function returns if player lost
bool player::getDidLose() const
{
	return didLose;
}

//This function checks if player lost
bool player::checkIfDidLose() const
{
	for (int col = 0; col < GAME_WIDTH; col++)
	{
		if (board[0][col] == 1)
			return true;
	}
	return false;
}

//This function is checking if the shape can move left, right or rotate if so it moves it
void player::movePieceLeftRight(char keyPressed) {

	shape tempShapeLeftRight;
	tempShapeLeftRight = currShape;														//Creating a temp shape for checking if curr shape can move
	tempShapeLeftRight.move(keyPressed);												//right or left or rotate
	if (checkIfShapeOnBoard(tempShapeLeftRight))
	{
		currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);	//Delete shape from screen
		deletePieceOnBoard(currShape);											//Remove shape from matrix
		Sleep(GameConfig::AVG_SLEEP);
		currShape.move(keyPressed);														//Moving the curr shape
		currShape.drawShape('#', color, minX);												//Drawing currshape on screen
		placePieceOnBoard(currShape);														//putting the coordinates in matrix
	}
}

//This function is checking if the shape can move down
bool player::checkMovePieceDown(const shape& s) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if ((getCoordInBoard(tmp) != 0) || (tmp.getY() >= GAME_HEIGHT))
			return false;
	}
	return true;
}

//This function is checking if shape is on board
bool player::checkIfShapeOnBoard(const shape& s) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if (isPointOnBoard(tmp) == false)
			return false;
	}
	return true;
}

//This function is for checking if the point is on the board
bool player::isPointOnBoard(const Point& p) const
{
	if ((p.getX() >= GAME_WIDTH) || (p.getX() < 0) || (p.getY() >= GAME_HEIGHT) || (p.getY() < 0))
		return false;
	return true;
}

//This function is for is for getting the shape coordinates
int player::getCoordInBoard(const Point& p) const
{
	int tempX, tempY;
	tempX = p.getX();
	tempY = p.getY();
	return board[tempY][tempX];
}

//This function is for is for updating the matrix (remove piece)
void player::deletePieceOnBoard(const shape& s)
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = s.getShape()[i].getX();
		tempY = s.getShape()[i].getY();
		board[tempY][tempX] = 0;
	}
}

//This function updates the new color for the pieces
void player::setColor(int color)
{
	this->color = color;
}

//This function clears the matrix
void player::clearBoard() {
	std::memset(board, 0, sizeof(board));
}

//This function is printing the new board on the screen
void player::PrintNewBoard() const
{
	for (int row = 0; row < GAME_HEIGHT; row++)										//Starts from 0 because we go over the matrix
	{
		for (int col = 0; col < (GAME_WIDTH); col++)
		{
			if (this->board[row][col] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);					//Change the background of the shape
				gotoxy(col + minX, row + START_HEIGHT);												//Because we print the board from 1,1
				cout << '#';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				gotoxy(col + minX, row + START_HEIGHT);												//Because we print the board from 1,1
				cout << ' ';
			}
		}
	}
}

//This function is for is for checking if theres a full line to be removed
void player::checkAndRemoveFullLinesOnBoard()
{

	for (int rows = GAME_HEIGHT - 1; rows >= 0; rows--)	//Here we look for a full line
	{
		bool isFull = true;
		for (int cols = 0; cols < (GAME_WIDTH) && (isFull); cols++)
		{
			if (board[rows][cols] == 0)
				isFull = false;
		}

		if (isFull)
		{
			removeLine(rows);											//Remove line
			deleteLineFromScreen(rows);									//Remove line from the screen
			moveLinesDown(rows);										//Moving all lines down
			PrintNewBoard();											//Prints the updated board
			rows++;														//To check for maybe if the same row is full again
		}
	}
}

//This function is for deleteing the line from the screen
void player::deleteLineFromScreen(int line)
{
	for (int x = minX; x < GAME_WIDTH + minX; x++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		gotoxy(x, line + 1);
		cout << ' ';
	}
}

//This function is for is for updating the matrix (moving pieces down)
void player::moveLinesDown(int line)
{
	for (int row = line; row >= 1; row--)
	{
		for (int col = 0; col < GAME_WIDTH; col++)
		{
			board[row][col] = board[row - 1][col];
		}
	}
}

//This function is for is for updating the matrix (remove line)
void player::removeLine(int line)
{

	for (int row = 0; row < GAME_WIDTH; row++)
	{
		board[line][row] = 0;
	}
}
//This function is adding piece to the matrix 
void player::placePieceOnBoard(const shape& s)
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = s.getShape()[i].getX();					//The shapes are printed 1 forward becuase of the boarder, so we update the board matrix correctly
		tempY = s.getShape()[i].getY();
		board[tempY][tempX] = 1;
	}
}

//This function is explodeing a bomb
void player::explodeBomb() //in the matrix not on screen
{
	int step = 1; 
	int width = 0, height = 0; //for the rectangle to delete
	int x = currShape.getShape()[0].getX(), y = currShape.getShape()[0].getY();//get the point of the bomb in the matrix
	int left=0, right=0, up=0, down=0; 

	for (step = 1; step <= NUM_OF_STEPS && (x + right < GAME_WIDTH-1); step++) //check that not up to 4 steps, and that the next step is in the matrix
		right++;

	for (step = 1; step <= NUM_OF_STEPS && (x - left > 0); step++) //check left limit
		left++;
	
	for (step = 1; step <= NUM_OF_STEPS && (y - up > 0); step++) //check upper limit
		up++;

	for (step = 1; step <= NUM_OF_STEPS && (y + down < GAME_HEIGHT-1); step++) //check down limit according to the matrix
		down++;

	width = left + right + 1; //1 for the bomb itself
	height = up + down + 1;

	for (int row = 0; row < height; row++) //delete the rectangle from the matrix
	{
		for (int col = 0; col < width; col++)
			board[row+y-up][col+x-left] = 0;  //gives us the up-left corner of the rectangle 
	}
	PrintNewBoard(); 
}