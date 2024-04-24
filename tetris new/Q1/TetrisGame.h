#ifndef __TETRISGAME_H
#define __TETRISGAME

#include <conio.h> // for kbhit+getch
#include <Windows.h> // for Sleep and colors
#include "gameConfig.h"
#include "point.h"
#include "shape.h"
#include "TetrisBoard.h"
#include <iostream>
#include <stdlib.h>
#include <limits> // for std::numeric_limits


using namespace std;


class TetrisGame
{
	TetrisBoard boardOne, boardTwo;
	bool newGame;
	int gameColor;

public:
	void initNewGame();
	void displayMenu();
	void handleMenuChoice(int choice);
	void displayInstructions();
	void runGame();
	void start();
	static constexpr int GRAY = 120;
	static constexpr int NUM_OF_ITERATIONS=3;
	static constexpr int WITH_COLORS =1;
	//static constexpr int WITHOUT_COLORS = 2;
	static constexpr int PLAYER1 = 1;
	static constexpr int PLAYER2 = 2;
};


#endif

