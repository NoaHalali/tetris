#include <Windows.h> // for Sleep and colors

#include "TetrisBoard.h"
#include "shape.h"

//This function is converting the char to the left ekeys 
char shape::convert(char direction) const
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
//This function is moving the shape
void shape::move(char direction)
{
	direction = convert(direction);								//Converting the left ekeys
	if (direction == GameConfig::eKeys_left::ROTATE_counter)
	{
		if (shapeNumber != 1)										//Not a square
			rotatePieceCounter();
	}
	if (direction == GameConfig::eKeys_left::ROTATE_clockwise)
	{
		if (shapeNumber != 1)										//Not a square
			rotatePieceClockwise();
	}
	if (direction == GameConfig::eKeys_left::LEFT || direction == GameConfig::eKeys_left::RIGHT)			//If its left or right then go to move in point
	{
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			piece[i].movePointLeftfOrRight(direction);
		}
	}

	if (direction == GameConfig::eKeys_left::DROP)															//If drop then move down an extra time
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)
		{
			piece[i].movePointDown();
		}
	}
}
//This function is moving the shape conter clockwise
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
//This function is moving the shape clockwise
void shape::rotatePieceClockwise()
{
	for (int i = 1; i < shape::NUM_OF_POINTS; ++i) {
		int relativeX = piece[i].getX() - piece[0].getX();
		int relativeY = piece[i].getY() - piece[0].getY();

		piece[i].set(piece[0].getX() - relativeY, piece[0].getY() + relativeX);
	}
}
//This function is drawing the shape 
void shape::drawShape(char ch, int color, int minX) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		piece[i].draw(ch, color, minX);
	}
}
//This function is initilising the shape 
void shape::init(int shapeNumber, char ch, int color)
{
	this->ch = ch;
	//this->backgroundcolor = color;
	this->shapeNumber = shapeNumber;
}


Point* shape::getShape() const
{
	return (Point*)piece;
}

//This function is the shape structure
void shape::setShape()
{
	switch (shapeNumber)
	{
	case SQUARE: //Squrae
		piece[0].set(GameConfig::MID_WIDTH_MATRIX, 0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX + 1,0);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX, 1);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX + 1, 1);
		break;

	case COLUMN: //Column 
		piece[0].set(GameConfig::MID_WIDTH_MATRIX, 0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX, 1);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX, 2);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX, 3);
		break;

	case HALF_PLUS: //Half + upsidedown
		piece[0].set(GameConfig::MID_WIDTH_MATRIX - 1,0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX, 0);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX + 1,0);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX , 1);
		break; 

	case J_BLOCK: //Like J
		piece[0].set(GameConfig::MID_WIDTH_MATRIX, 0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX, 1);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX, 2);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX - 1, 2);

		break;

	case L_BLOCK: //Like L
		piece[0].set(GameConfig::MID_WIDTH_MATRIX - 1, 0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX - 1, 1);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX - 1, 2);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX, 2);

		break;

	case S_BLOCK: //Egypian hands right
		piece[0].set(GameConfig::MID_WIDTH_MATRIX  - 1, 1);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX,0);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX,  1);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX + 1,0);

		break;

	case Z_BLOCK: //Egypian hands left
		piece[0].set(GameConfig::MID_WIDTH_MATRIX - 1, 0);
		piece[1].set(GameConfig::MID_WIDTH_MATRIX, 0);
		piece[2].set(GameConfig::MID_WIDTH_MATRIX,  1);
		piece[3].set(GameConfig::MID_WIDTH_MATRIX + 1, 1);
		break;

	case BOMB:
		for (int i = 0; i < NUM_OF_POINTS; i++)
			piece[i].set(GameConfig::MID_WIDTH_MATRIX,0);
		break;
	}
}


