#include "TetrisBoard.h"
#include <iostream>
#include "point.h"
#include <Windows.h>
#include <conio.h> // for kbhit+getch
using namespace std;



//This function is for drawing both players boards
void TetrisBoard::drawBorder() const
{
	for (int col = minX; col < minX + TetrisBoard::GAME_WIDTH; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, TetrisBoard::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::MIN_Y + TetrisBoard::GAME_HEIGHT; row++)
	{
		gotoxy(minX - 1, row);
		cout << "|";

		gotoxy(TetrisBoard::GAME_WIDTH + minX, row);
		cout << "|";
	}
}


//This function is creating a new shape 
shape TetrisBoard::giveMeShape()
{
	shape s;
	int numOfShape;
	//double val = (double)rand() / RAND_MAX; //get random double for percent
	
	//if (val < GameConfig::CHANCES_FOR_REGULAR_SHAPE)		//chance for regular shapes
		numOfShape = rand() % (TetrisBoard::NUM_OF_SHAPES)+1;
	//else	//It's bomb time!
	//	numOfShape = shape::BOMB;

	s.init(numOfShape, '#', color);			//Updating random shape and the color
	//s.init(rand() % (TetrisBoard::NUM_OF_SHAPES)+1, '#', color);									//Updating random shape and the color
	s.setShape();
	currShape = s;
	this->placePieceOnBoard();																		//Putting shape in the matrix
	if (color == GameConfig::BLACK)
		currShape.drawShape('#', color, minX);																//Drawing the shape on screen
	else
	{
		int i = rand() % GameConfig::NUM_OF_COLORS;
		color = GameConfig::COLORS_ARRAY[(i % (GameConfig::NUM_OF_COLORS - 1)) + 1];
		currShape.drawShape('#', color,minX);
	}
	Sleep(GameConfig::SLEEP_TIME);
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);					//Delete shape from screen
	deletePieceOnBoard(currShape);															//Delete shape from matrix

	return s;
}

//This function gets a shape, checks if its possible to move it down on the screen and on the matrix and if so it moves it
bool TetrisBoard::isPieceMovedDown()
{
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);					//Delete shape from screen
	this->deletePieceOnBoard(currShape);															//Delete shape from matrix
	bool isShapeCanMove = true;
	shape tempShapeDown = currShape;																//Temp shape to check if shape can move
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)													//Moving the temp shape 
	{
		tempShapeDown.getShape()[i].movePointDown();
	}
	if (this->checkMovePieceDown(tempShapeDown))													//Checking if temp shape is in an approved place if so we move the curr shape
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)												//Moving curr shape
		{
			currShape.getShape()[i].movePointDown();
		}
		this->placePieceOnBoard();																	//Putting shape in the matrix
		currShape.drawShape('#', color, minX);															//Drawing the shape on screen
		Sleep(GameConfig::AVG_SLEEP);

	}
	else
	{
		currShape.drawShape('#', color, minX);															//Keep the shape where it was before trying to move
		placePieceOnBoard();																	//Putting shape in the matrix
		isShapeCanMove = false;																		//Cant move anymore
		checkAndRemoveFullLinesOnBoard();																//checking if line is full to delete
		if (checkIfDidLose() == TRUE)																//Checking if one player got to the last line
			didLose = true;
	}
	return isShapeCanMove;
}
//This function is returning the data member did lose
bool TetrisBoard::getDidLose() const
{
	return didLose;
}
//This function is checking if a player has any pieces in the first line of the board meaning if he lost
bool TetrisBoard::checkIfDidLose() const
{
	for (int col = 0; col < GAME_WIDTH; col++)
	{
		if (board[0][col] == 1)
			return true;
	}
	return false;
}
//This function is checking if the shape can move left, right or rotate if so it moves it
void TetrisBoard::movePieceLeftRight(char keyPressed) {

	shape tempShapeLeftRight;
	tempShapeLeftRight = currShape;														//Creating a temp shape for checking if curr shape can move
	tempShapeLeftRight.move(keyPressed);												//right or left or rotate
	if (checkMovePieceRightAndLeft(tempShapeLeftRight))
	{
		currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);	//Delete shape from screen
		deletePieceOnBoard(currShape);											//Remove shape from matrix
		Sleep(GameConfig::AVG_SLEEP);
		currShape.move(keyPressed);														//Moving the curr shape
		currShape.drawShape('#', color, minX);												//Drawing currshape on screen
		placePieceOnBoard();														//putting the coordinates in matrix
	}
}
//This function is for moving the pieces on the board
void TetrisBoard::move(char keyPressed)
{
	if (isPieceMovedDown())																		//Moving down
	{
		if (keyPressed == GameConfig::eKeys_right::DROP || keyPressed == GameConfig::eKeys_left::DROP)	//If the key pressed is drop
			isPieceMovedDown();
		else if (keyPressed != 0)																		//Any other key pressed
			movePieceLeftRight(keyPressed);
	}
	else
	{
		if (!didLose)
		{
			//if (currShape.getShapeNumber() == shape::BOMB)
			//	this->explodeBomb();

			giveMeShape();																	//New shape
		}
	}
}
//This function is for checking if the shape can move down
bool TetrisBoard::checkMovePieceDown(const shape& s) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if ((getCoordInBoard(tmp) != 0) || (tmp.getY() >= GAME_HEIGHT))
			return false;
	}
	return true;
}
//This function is for checking if the shape can move right or left or rotate
bool TetrisBoard::checkMovePieceRightAndLeft(const shape& s) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if (isPointOnBoard(tmp) == false)
			return false;
	}
	return true;
}
//This function is for updating the matrix (add piece)
void TetrisBoard::placePieceOnBoard() //שינינו במחלקה של המחשב
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = currShape.getShape()[i].getX();					//The shapes are printed 1 forward becuase of the boarder, so we update the board matrix correctly
		tempY = currShape.getShape()[i].getY();
		board[tempY][tempX] = 1;
	}
}
//This function is for is for updating the matrix (remove piece)
void TetrisBoard::deletePieceOnBoard(const shape& s)
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = s.getShape()[i].getX();
		tempY = s.getShape()[i].getY();
		board[tempY][tempX] = 0;
	}
}
//This function is for is for getting the shape coordinates
int TetrisBoard::getCoordInBoard(const Point& p) const
{
	int tempX, tempY;
	tempX = p.getX();
	tempY = p.getY();
	return board[tempY][tempX];
}
//This function is for checking if the point is on the board
bool TetrisBoard::isPointOnBoard(const Point& p) const
{
	if ((p.getX() >= GAME_WIDTH) || (p.getX() < 0) || (p.getY() >= GAME_HEIGHT))
		return false;
	return true;
}
//This function is for is for checking if theres a full line to be removed
void TetrisBoard::checkAndRemoveFullLinesOnBoard()
{
	for (int rows = TetrisBoard::GAME_HEIGHT - 1; rows >= 0; rows--)	//Here we look for a full line
	{
		bool isFull = true;
		for (int cols = 0; cols < (TetrisBoard::GAME_WIDTH) && (isFull); cols++)
		{
			if (board[rows][cols] == 0)
				isFull = false;
		}

		if (isFull)
		{
			removeLine(rows);											//Remove line
			deleteLineFromScreen(rows);							//Remove line from the screen
			moveLinesDown(rows);										//Moving all lines down
			PrintNewBoard();											//Prints the updated board
			rows++;														//To check for maybe if the same row is full again
		}
	}
}
//This function is for deleteing the line from the screen
void TetrisBoard::deleteLineFromScreen(int line)
{
	for (int x = minX; x < TetrisBoard::GAME_WIDTH + minX; x++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		gotoxy(x, line + 1);
		cout << ' ';
	}
}
//This function is for is for updating the matrix (moving pieces down)
void TetrisBoard::moveLinesDown(int line)
{
	for (int row = line; row >= 1; row--)
	{
		for (int col = 0; col < TetrisBoard::GAME_WIDTH; col++)
		{
			board[row][col] = board[row - 1][col];
		}
	}
}
//This function is for is for updating the matrix (remove line)
void TetrisBoard::removeLine(int line)
{

	for (int row = 0; row < TetrisBoard::GAME_WIDTH; row++)
	{
		board[line][row] = 0;
	}
}
//This function is printing the new board on the screen
void TetrisBoard::PrintNewBoard() const
{
	for (int row = 0; row < TetrisBoard::GAME_HEIGHT; row++)										//Starts from 0 because we go over the matrix
	{
		for (int col = 0; col < (TetrisBoard::GAME_WIDTH); col++)
		{
			if (board[row][col] == 1)
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
//This function is initilising the board for each player
void TetrisBoard::init(int minX, int color, int playerNumber)
{
	this->clearBoard();
	this->color = color;
	this->minX = minX;
	this->drawBorder();
	this->currShape = giveMeShape();
	this->didLose = false;
	this->playerNum = playerNum;
}
//This function clears the matrix
void TetrisBoard::clearBoard() {
	std::memset(board, 0, sizeof(board));
}
//This function updates the new color for the pieces
void TetrisBoard::setColor(int color)
{
	this->color = color;
}

//void TetrisBoard::explodeBomb() //במטריצה ולא במסך!
//{
//	int step = 1; 
//	int width = 0, height = 0; //for the rectangle to delete
//	int x = currShape.getShape()[0].getX() -minX, y = currShape.getShape()[0].getY()-START_HEIGHT;//get the point of the bomb in the matrix
//	int left=0, right=0, up=0, down=0; 
//	//int tempX, tempY;
//
//	for (step = 1; step <= NUM_OF_STEPS && (x + right < GAME_WIDTH-1); step++) //check that not up to 4 steps, and that it in the border limits
//		right++;
//
//	for (step = 1; step <= NUM_OF_STEPS && (x - left > 0); step++) //check left limit
//		left++;
//	
//	for (step = 1; step <= NUM_OF_STEPS && (y - up > 0); step++) //check upper limit
//		up++;
//
//	for (step = 1; step <= NUM_OF_STEPS && (y + down < GAME_HEIGHT-1); step++) //check down limit
//		down++;
//
//	width = left + right + 1; //1 for the bomb itself
//	height = up + down + 1;
//
//	for (int row = 0; row < height; row++) //delete the rectangle from the matrix
//	{
//		for (int col = 0; col < width; col++)
//			board[row+y-up][col+x-left] = 0;  //gives us the up-left corner of the rectangle 
//	}
//	PrintNewBoard(); 

	/* 
	לחשוב מה עושים עם נקודות שאמורות ליפול 
	להדפיס את הלוח שוב*/
	//לטפל בצבעים אם יש זמן


	//הגדלנו את הסיכויים לפצצה בשביל הבדיקות אז לא לשכוח לשנות!
	//while ((step <= NUM_OF_STEPS) && (right < GAME_WIDTH + minX)) //check right limit 
	//{
	//	right++;
	//	step++;
	//}	
//}