#ifndef __SHAPE_H
#define __SHAPE_H
#include "point.h"

class shape
{
public:
	static constexpr int NUM_OF_POINTS = 4;
	void setShape(int minX);
	void init(int shapeNumber, char ch, int color);
	void move(char direction);
	void drawShape(char ch, int color);
	char convert(char direction);
	void rotatePieceClockwise();
	void rotatePieceCounter();
	Point* getShape();
	static constexpr int MOVE_DOWN = 0;
private:
	int backgroundcolor;
	int shapeNumber; //between 1-7 
	char ch;
	Point piece[NUM_OF_POINTS];

};
#endif

