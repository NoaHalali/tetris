#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"

class shape
{
public:
	void setShape();
	void init(int shapeNumber, char ch, int color);
	void move(char direction);
	void drawShape(char ch, int color, int minX) const;
	char convert(char direction) const;
	void rotatePieceClockwise();
	void rotatePieceCounter();
	Point* getShape() const;
	int getShapeNumber() const{ return shapeNumber; };

	enum {SQUARE =1, COLUMN=2, HALF_PLUS=3 ,J_BLOCK=4, L_BLOCK =5, S_BLOCK=6, Z_BLOCK=7, BOMB=8};
	static constexpr int NUM_OF_POINTS = 4;
	static constexpr int MOVE_DOWN = 0;
	static constexpr int ONE_CLOCKWISE_ROTATION =1;
	static constexpr int TWO_CLOCKWISE_ROTATION =2;


private:
	int shapeNumber;			//between 1-7 
	char ch;					//The shape char
	Point piece[NUM_OF_POINTS];	//Shape is an array or 4 point

};
#endif