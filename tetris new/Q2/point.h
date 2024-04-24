#ifndef __POINT_H
#define __POINT_H

#include "gameConfig.h"

using std::cout;

class Point
{
	int x;
	int y;
public:
	void set(int x, int y);
	void draw(char ch, int backcolor, int minX) const;
	void movePointLeftfOrRight(char direction);
	int getX() const { return x; }; 
	int getY() const { return y; };
	void movePointDown();
};

#endif