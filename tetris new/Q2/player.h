#ifndef __PLAYER_H
#define __PLAYER_H


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h> // for kbhit+getch
#include "shape.h"
using std::cin;
using std::cout;
using std::endl;

class player
{
public:

	static constexpr int GAME_WIDTH = 12;									//12 for the frame
	static constexpr int GAME_HEIGHT = 18;									//18 for the frame
	static constexpr int NUM_OF_SHAPES = 7;									//There are 7 possible shapes 
	static constexpr int MID_WIDTH = 6;										//The middle of the board 
	static constexpr int START_HEIGHT = 1;									//The beginning height of every piece
	static constexpr int NUM_OF_STEPS = 4;

	player(int minX, int color, int playerNumber);
	void drawBorder() const;												//Drawing the board
	void placePieceOnBoard(const shape& s);									//Putting the coords in the matrix
	void deletePieceOnBoard(const shape& s);								//Removing the points from the matrix
	int getCoordInBoard(const Point& p) const;								//Getting the coords
	bool isPointOnBoard(const Point& p) const;								//Checking if point on board
	bool checkMovePieceDown(const shape& s) const;
	bool checkIfShapeOnBoard(const shape& s) const;							//Checking if can move left right
	void checkAndRemoveFullLinesOnBoard();									//Checking if there are full lines and remove them
	bool getDidLose() const;												//Getting the player status in game
	bool checkIfDidLose() const;											//Checking if a player lost
	void removeLine(int line);												//Remving the line from board and screen
	void moveLinesDown(int line);											//Moving boards lines down
	void deleteLineFromScreen(int line);									//Delete the line from the screen
	void PrintNewBoard() const;												//Print the new board updated
	virtual void giveMeShape()=0;											//Get new shape
	bool checkAndMovePieceDown();											//Check if piece moved down
	void movePieceLeftRight(char keyPressed);								//Moving the shape left or right
	virtual void calcMove(char keyPressed)=0 ;								//Moving the shape
	void clearBoard();														//Clear the matrix
	void setColor(int color);
	virtual void move()=0;
	void explodeBomb();
	virtual ~player() {};

protected:

	int board[GAME_HEIGHT][GAME_WIDTH];										//The matrix
	int color;
	int minX;																//Where the board begins
	shape currShape;														//Current shape on board
	bool didLose;															//Chcek for if player lost if shapes reach the top
	int playerNum;
	char currMove;

};

#endif