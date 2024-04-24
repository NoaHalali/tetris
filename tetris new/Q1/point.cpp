#include "point.h"
#include "gameConfig.h"
//#include "general.h"
#include "TetrisBoard.h"

#include <iostream>
#include <Windows.h>
using namespace std;

void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;

}
void Point::draw(char ch, int backcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor); //remove backgroung color for point
	gotoxy(x , y); 
	cout << ch;
}

void Point::movePointLeftfOrRight(char direction) 
{
	int newX = this->getX();
	//newY= this->getY()+1;
	switch (direction)
	{
	case 'A'://LEFT
		newX= newX-1;
		break;
	case 'D'://RIGHT
		newX = newX + 1;
		break;
	}

	this->set(newX, this->getY());
}

void Point::movePointDown() {
	int  newY = this->getY() + 1;
	this->set(this->getX(), newY);
}