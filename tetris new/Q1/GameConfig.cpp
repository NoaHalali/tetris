#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "gameConfig.h"
using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//int GameConfig:: convert(int direction) 
//{
//	if (direction >= 'a' && direction <= 'z')
//		direction -= 32;
//	if (direction == 'J')
//		direction = 'A';
//	if (direction == 'L')
//		direction = 'D';
//	if (direction == 'K')
//		direction = 'S';
//	if (direction == 'I')
//		direction = 'W';
//	if (direction == 'M')
//		direction = 'X';
//
//	return direction;
//}
void clrscr()
{
	system("cls");
}

