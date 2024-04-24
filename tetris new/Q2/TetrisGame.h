#ifndef __TETRISGAME_H
#define __TETRISGAME_H

#include <conio.h>							//for kbhit+getch
#include <Windows.h>						//for Sleep and colors
#include <iostream>
#include <stdlib.h>

#include "gameConfig.h"
#include "point.h"
#include "shape.h"
#include "humanPlayer.h"
#include "player.h"
#include "Computer.h"

using std::cout;
using std::cin;
using std::endl;

class TetrisGame
{
	player* p1, * p2;		//two players according to the choice of the user
	bool newGame;			
	int gameColor;

	TetrisGame(const TetrisGame& other); //delete default copy ctor
public:
	TetrisGame() {};					//empty ctor
	void initNewGameHumans();			//if user choice is two human players
	void initNewGameComputers();		//if user choice is two computers
	void initNewGameHumanVsComputer();	//if user choice is against computer
	void displayMenu() const;			
	void handleMenuChoice(int choice);
	void displayInstructions() const;
	void runGame();
	void start();

	static constexpr int COLORFUL = 120;			//Colours for the shapes
	static constexpr int NUM_OF_ITERATIONS = 3;		//Gets 3 keypressed in each round
	static constexpr int WITH_COLORS = 1;			//Menu choice
};


#endif