#include "shape.h"
#include <Windows.h> // for Sleep and colors
#include "TetrisBoard.h"

char shape::convert(char direction)
{
	if (direction == GameConfig::eKeys_right::LEFT)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::LEFT);
	if (direction == GameConfig::eKeys_right::RIGHT)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::RIGHT);
	if (direction == GameConfig::eKeys_right::ROTATE_clockwise)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::ROTATE_clockwise);
	if (direction == GameConfig::eKeys_right::ROTATE_counter)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::ROTATE_counter);
	if (direction == GameConfig::eKeys_right::DROP)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::DROP);

	return direction;
}

void shape::move(char direction)
{
	direction = convert(direction);
	if (direction == GameConfig::eKeys_left::ROTATE_counter)
	{
		if (shapeNumber != 1)//not a square
			rotatePieceCounter();
	}
	if (direction == GameConfig::eKeys_left::ROTATE_clockwise)
	{
		if (shapeNumber != 1)//not a square
			rotatePieceClockwise();
	}
	if (direction == GameConfig::eKeys_left::LEFT || direction == GameConfig::eKeys_left::RIGHT)//if its left or right then go to move in point
	{
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			piece[i].movePointLeftfOrRight(direction);
		}
	}

	if (direction == GameConfig::eKeys_left::DROP)
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)
		{
			piece[i].movePointDown();
		}
	}
} 
void shape::rotatePieceCounter()
{
	// Assuming the rotation is around the first point (piece[0])
	for (int i = 1; i < shape::NUM_OF_POINTS; ++i) {
		int relativeX = piece[i].getX() - piece[0].getX();
		int relativeY = piece[i].getY() - piece[0].getY();

		// Rotate the point relative to the first point
		piece[i].set(piece[0].getX() + relativeY, piece[0].getY() - relativeX);
	}
}

void shape::rotatePieceClockwise()
{
	for (int i = 1; i < shape::NUM_OF_POINTS; ++i) {
		int relativeX = piece[i].getX() - piece[0].getX();
		int relativeY = piece[i].getY() - piece[0].getY();

		piece[i].set(piece[0].getX() - relativeY, piece[0].getY() + relativeX);
	}
}

void shape::drawShape(char ch, int color)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		piece[i].draw(ch, color);
	}
}
void shape::init(int shapeNumber, char ch, int color)
{
	this->ch = ch;
	this->backgroundcolor = color;
	this->shapeNumber = shapeNumber;
}
void shape:: setShape(int minX) 
{
	switch (shapeNumber)
	{
	case 1: //ריבוע
		piece[0].set(TetrisBoard::MID_WIDTH + minX,TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX +1, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX +1, TetrisBoard::START_HEIGHT+1);
		break;
	
	case 2: //עמוד
		piece[0].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+3);
		break;
	
	case 3: //חצי פלוס הפוך
		piece[0].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX +1, TetrisBoard::START_HEIGHT);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		break;
	
	case 4: //נ
		piece[0].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT+2);

		break;
	
	case 5: // נ הפוכה מראה
		piece[0].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT+1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT+2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+2);

		break;
	
	case 6: //יד מצרית ימנית
		piece[0].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT+1);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX +1, TetrisBoard::START_HEIGHT);

		break;	
	case 7: //יד מצרית שמאלית
		piece[0].set(TetrisBoard::MID_WIDTH + minX -1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT+1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX +1, TetrisBoard::START_HEIGHT+1);

		break;
	}
}

Point* shape:: getShape()
{
	return piece;
}


