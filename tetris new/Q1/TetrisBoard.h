#ifndef __TETRISBOARD_H
#define __TETRISBOARD

#include "shape.h"
class shape;
class TetrisBoard
{
public:
	static constexpr int GAME_WIDTH = 12;									//12 for the frame
	static constexpr int GAME_HEIGHT = 18;									//18 for the frame
	static constexpr int NUM_OF_SHAPES = 7;									//there are 7 possible shapes 
	static constexpr int MID_WIDTH = 6;										//the middle of the board 
	static constexpr int START_HEIGHT = 1;									//the beginning height of every piece



	void drawBorder();
	void placePieceOnBoard();
	void deletePieceOnBoard(shape s);
	int getCoordInBoard(Point p);
	bool isPointOnBoard(Point p);
	bool checkMovePieceDown(shape s);
	bool checkMovePieceRightAndLeft(shape s);
	void checkFullLinesOnBoard();
	bool getDidLose();
	bool checkIfDidLose();
	void removeLine(int line);
	void moveLinesDown(int line);
	void deleteLineFromScreen(int line);
	void PrintNewBoard();
	shape giveMeShape();
	bool isPieceMovedDown();
	void movePieceLeftRight(char keyPressed);
	void move(char keyPressed);
	void init(int minX, int color);
	void clearBoard();
	void setColor(int color);



private:
	//int board[GAME_HEIGHT][GAME_WIDTH] = {};
	int board[GAME_HEIGHT][GAME_WIDTH];
	int color;
	int minX; // where the board begins
	shape currShape;
	bool didLose;
	int playerNum;
};

#endif
