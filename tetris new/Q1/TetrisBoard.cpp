#include "TetrisBoard.h"
#include <iostream>
#include "point.h"
#include <Windows.h>
#include <conio.h> // for kbhit+getch
using namespace std;



//This function is for drawing both players boards
void TetrisBoard::drawBorder()
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


//This funv
shape TetrisBoard::giveMeShape()
{
	shape s;
	s.init(rand() % (TetrisBoard::NUM_OF_SHAPES) + 1, '#',color);
	s.setShape(minX);
	currShape = s;
	this->placePieceOnBoard();
	currShape.drawShape('#', color);
	Sleep(50);
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //delete shape
	this->deletePieceOnBoard(currShape);

	return s;
}

bool TetrisBoard::isPieceMovedDown()
{
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //delete shape
	this->deletePieceOnBoard(currShape);
	bool isShapeCanMove = true;
	shape tempShapeDown = currShape;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)//down
	{
		tempShapeDown.getShape()[i].movePointDown();
	}
	if (this->checkMovePieceDown(tempShapeDown))
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)
		{
			currShape.getShape()[i].movePointDown();
		}
		this->placePieceOnBoard();
		currShape.drawShape('#',color);
		Sleep(200);

	}
	else
	{
		currShape.drawShape('#',color); //keep the shape where she was before trying to move
		this->placePieceOnBoard();
		isShapeCanMove = false;
		this->checkFullLinesOnBoard();
		if (checkIfDidLose() == TRUE)
			didLose = true;
	}
	return isShapeCanMove;
}
bool TetrisBoard:: getDidLose()
{
	return didLose;
}

bool TetrisBoard::checkIfDidLose()
{
	for (int col = 0; col < GAME_WIDTH; col++)
	{
		if (board[0][col] == 1)
			return true;
	}
	return false;
}

void TetrisBoard::movePieceLeftRight(char keyPressed) {

	shape tempShapeLeftRight;
	tempShapeLeftRight = currShape;
	tempShapeLeftRight.move(keyPressed); //right or left or rotate
	if (this->checkMovePieceRightAndLeft(tempShapeLeftRight))
	{
		currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //delete shape
		this->deletePieceOnBoard(currShape);
		Sleep(200);
		currShape.move(keyPressed);
		currShape.drawShape('#',color);
		this->placePieceOnBoard();
	}
}

void TetrisBoard::move(char keyPressed)
{
	if (this->isPieceMovedDown()) 
	{
		if (keyPressed == GameConfig::eKeys_right::DROP || keyPressed == GameConfig::eKeys_left::DROP)
			this->isPieceMovedDown();
		else if (keyPressed != 0)
			movePieceLeftRight(keyPressed);
	}
	else
		this->giveMeShape();					//new shape

}
bool TetrisBoard::checkMovePieceDown(shape s)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if ((this->getCoordInBoard(tmp) != 0) || (tmp.getY() >= GAME_HEIGHT + 1))
			return false;
	}
	return true;
}

bool TetrisBoard::checkMovePieceRightAndLeft(shape s)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if (this->isPointOnBoard(tmp) == false)
			return false;
	}
	return true;
}


void TetrisBoard::placePieceOnBoard()
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = currShape.getShape()[i].getX() - minX;//the shapes are printed 1 forward becuase of the boarder, so we update the board matrix correctly
		tempY = currShape.getShape()[i].getY() -START_HEIGHT;
		this->board[tempY][tempX] = 1;
	}
}
void TetrisBoard::deletePieceOnBoard(shape s)
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = s.getShape()[i].getX() - minX;
		tempY = s.getShape()[i].getY() - START_HEIGHT;
		this->board[tempY][tempX] = 0;
	}
}

int TetrisBoard::getCoordInBoard(Point p)
{
	int tempX, tempY;
	tempX = p.getX() - minX;
	tempY = p.getY() - START_HEIGHT;
	return this->board[tempY][tempX];
}

bool TetrisBoard::isPointOnBoard(Point p)
{
	if ((p.getX() >= GAME_WIDTH + minX) || (p.getX() <= minX - 1) || (p.getY() >= GAME_HEIGHT))
		return false;
	return true;
}

void TetrisBoard::checkFullLinesOnBoard()
{
	//לבדוק אופציה אם צריך למחוק יותר מאחת וגם לשמור את הגובה המקסימלי במקום לעבור על כל השורות
	for (int rows = TetrisBoard::GAME_HEIGHT - 1; rows >= 0; rows--)
	{
		bool isFull = true;
		for (int cols = 0; cols < (TetrisBoard::GAME_WIDTH) && (isFull); cols++)
		{
			if (this->board[rows][cols] == 0)
				isFull = false;
		}

		if (isFull)
		{
			removeLine(rows);//remove line
			this->deleteLineFromScreen(rows);
			moveLinesDown(rows);
			PrintNewBoard();
			rows++;//to check for maybe if the same row is full again
		}
	}
	//move points down
}

void TetrisBoard::deleteLineFromScreen(int line)
{
	for (int x = minX; x < TetrisBoard::GAME_WIDTH+minX; x++)
	{
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE, );
		gotoxy(x, line + 1);
		cout << ' ';
	}
}
void TetrisBoard::moveLinesDown(int line)
{
	for (int row = line; row >= 1; row--)
	{
		for (int col = 0; col < TetrisBoard::GAME_WIDTH; col++)
		{
			this->board[row][col] = this->board[row - 1][col];
		}
	}
	//removeLine(0);
}
void TetrisBoard::removeLine(int line)
{

	for (int row = 0; row < TetrisBoard::GAME_WIDTH; row++)
	{
		board[line][row] = 0;
	}
}
void TetrisBoard::PrintNewBoard()
{
	for (int row = 0; row < TetrisBoard::GAME_HEIGHT; row++)// starts from 0 because we go over the matrix
	{
		for (int col = 0; col < (TetrisBoard::GAME_WIDTH ); col++)
		{
			if (this->board[row][col] == 1)
			{
				//for next project we'll add colors
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); //change the background of the shape
				gotoxy(col + minX , row + START_HEIGHT); //Because we print the board from 1,1
				cout << '#';
			}
			else
			{
				//for next project we'll add colors
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				gotoxy(col + minX, row + START_HEIGHT);//Because we print the board from 1,1
				cout << ' ';
			}
		}
	}
}
void TetrisBoard::init(int minX, int color)
{
	this->clearBoard();
	this->color = color;
	this->minX = minX;
	this->drawBorder();
	this->currShape = giveMeShape();
	this->didLose = false;
	this->playerNum = playerNum;
}



void TetrisBoard::clearBoard() {
	std::memset(board, 0,sizeof(board));
}

void TetrisBoard::setColor(int color)
{
	this->color = color;
}