#include "humanPlayer.h"

//This function is creating a new shape 
void humanPlayer::giveMeShape()
{
	shape s;
	int numOfShape;
	double val = (double)rand() / RAND_MAX; //get random double for percent

	if (val < GameConfig::CHANCES_FOR_REGULAR_SHAPE)		//chance for regular shapes
		numOfShape = rand() % (humanPlayer::NUM_OF_SHAPES)+1;
	else	//It's bomb time!
		numOfShape = shape::BOMB;

	s.init(numOfShape, '#', color);			//Updating random shape and the color
	s.setShape();
	currShape = s;
	placePieceOnBoard(currShape);																		//Putting shape in the matrix
	if (color == GameConfig::BLACK)
		currShape.drawShape('#', color, minX);																//Drawing the shape on screen
	else
	{
		int i = rand() % GameConfig::NUM_OF_COLORS;
		color = GameConfig::COLORS_ARRAY[(i % (GameConfig::NUM_OF_COLORS - 1)) + 1];
		currShape.drawShape('#', color, minX);
	}
	Sleep(GameConfig::SLEEP_TIME);
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, minX);					//Delete shape from screen
	deletePieceOnBoard(currShape);															//Delete shape from matrix

}

//This function is calculate the next player move
void humanPlayer::calcMove(char keyPressed)
{
	if (playerNum == GameConfig::LEFT_PLAYER)
	{
		if (keyPressed == GameConfig::eKeys_left::LEFT || keyPressed == GameConfig::eKeys_left::RIGHT ||
			keyPressed == GameConfig::eKeys_left::ROTATE_clockwise || keyPressed == GameConfig::eKeys_left::ROTATE_counter ||
			keyPressed == GameConfig::eKeys_left::DROP)
		{
			currMove = keyPressed;
		}
		else
			currMove = shape::MOVE_DOWN;
	}
	else//check if the key is for player right
	{
		if (keyPressed == GameConfig::eKeys_right::LEFT || keyPressed == GameConfig::eKeys_right::RIGHT ||
			keyPressed == GameConfig::eKeys_right::ROTATE_clockwise || keyPressed == GameConfig::eKeys_right::ROTATE_counter ||
			keyPressed == GameConfig::eKeys_right::DROP)
		{
			currMove = keyPressed;
		}
		else
			currMove = shape::MOVE_DOWN;

	}
}

//This function is for moving the pieces on the board
void humanPlayer::move()
{
	if (checkAndMovePieceDown())																		//Moving down
	{
		if (currMove == GameConfig::eKeys_right::DROP || currMove == GameConfig::eKeys_left::DROP)	//If the key pressed is drop
			checkAndMovePieceDown();
		else if (currMove != 0)																		//Any other key pressed
			movePieceLeftRight(currMove);
	}
	else
	{
		if (!didLose)
		{
			if (currShape.getShapeNumber() == shape::BOMB)
				this->explodeBomb();

			giveMeShape();																	//New shape
		}
	}
}
