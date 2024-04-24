#include "Computer.h"

//This function is creating a new shape and update the shape's track
void Computer::giveMeShape()
{
	shape s;
	int numOfShape;
	double val = (double)rand() / RAND_MAX; //get random double for percent

	if (val < GameConfig::CHANCES_FOR_REGULAR_SHAPE)		//chance for regular shapes
		numOfShape = rand() % (Computer::NUM_OF_SHAPES)+1;
	else	//It's bomb time!
		numOfShape = shape::BOMB;

	s.init(numOfShape, '#', color);			//Updating random shape and the color
	s.setShape();
	currShape = s;
	this->placePieceOnBoard(currShape);																		//Putting shape in the matrix
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
	deletePieceOnBoard(currShape);																			//Delete shape from matrix
	findAndUpdateBestTrack();																				//updtaes track
}

//This function is finding and updates the currShape track
void Computer::findAndUpdateBestTrack()
{
	bool canMove = true;
	int downCounter = 0, leftMoves = 0;
	shape tempShape;
	shape currShapeSaver = currShape; //saving the original shape
	bestMove rotationsArr[GameConfig::NUM_OF_ROTATIONS] = {}; // array for the best moves of the 4 different rotation

	for (int rotation = 0; rotation < GameConfig::NUM_OF_ROTATIONS; rotation++)
	{
		currShape = currShapeSaver;
		canMove = true;
		leftMoves = 0;
		
		int removedLinesCounter[GAME_WIDTH] = {};   //initilaizing the counters for removing lines for each coloumn
		int downCounters[GAME_WIDTH] = {};	//initilaizing the counters for going down in each coloumn

		//specific checks forr different shape types for maximized efficiency
		if (currShape.getShapeNumber() == shape::SQUARE && rotation >= shape::ONE_CLOCKWISE_ROTATION) //square needs only one check rotation
			break;
		if (currShape.getShapeNumber() == shape::COLUMN && rotation >= shape::TWO_CLOCKWISE_ROTATION) //column needs only two check rotation
			break;
		if (currShape.getShapeNumber() == shape::S_BLOCK)	//S block is moving one down on second rotation
		{
			if (rotation == shape::ONE_CLOCKWISE_ROTATION)
			{
				for (int i = 0; i < shape::NUM_OF_POINTS; i++)
				{
					currShape.getShape()[i].set(currShape.getShape()[i].getX(), currShape.getShape()[i].getY()-1);
				}
			}
			if (rotation >= shape::TWO_CLOCKWISE_ROTATION)//theres only two rotations for s block
				break;
		}
		if (currShape.getShapeNumber() == shape::Z_BLOCK && rotation >= shape::TWO_CLOCKWISE_ROTATION)
			break;


		//start checking for the best move
		for (int i = 0; i < rotation; i++)
			currShape.rotatePieceClockwise();
		
		//check if after rotation the shape still on board and fix it if needed
		if (!checkIfShapeOnBoard(currShape))  
		{
			int min = 0;
			for (int i = 0; i < shape::NUM_OF_POINTS; i++) {//find min y when rotating
				if (min > currShape.getShape()[i].getY())
					min = currShape.getShape()[i].getY();
			}
			int diffY = -min;
			for(int i=0;i< diffY;i++)
				currShape.move((char)GameConfig::eKeys_left::DROP);
		}

		tempShape = currShape;

		//checking with temp shape to ensure right calcutation of left move
		for (int i = 0; i < MID_WIDTH && canMove; i++)
		{
			tempShape.move((char)GameConfig::eKeys_left::LEFT);									
			if (this->checkIfShapeOnBoard(tempShape)) 
				leftMoves++;
			else
				canMove = false;
		}

		//moving the curr shape to the upper left corner
		for (int i = 0; i < leftMoves; i++) 
		{
			movePieceLeftRightForBestMove((char)GameConfig::eKeys_left::LEFT, currShape);
		}

		tempShape = currShape; //saving the shape on the upper left corner of the matrix

		//going through all the columns to check which one is the best
		for (int col = 0; col < GAME_WIDTH && checMoveForLeftRightForBestMove(currShape); col++) 
		{
			downCounter = 0;
			currShape = tempShape; //returning the shape to the upper left corner of the matrix

			//moving for the coloumn of the current check
			for (int j = 0; j < col; j++)
				movePieceLeftRightForBestMove((char)GameConfig::eKeys_left::RIGHT, currShape);

			deletePieceOnBoard(currShape);
			while (checkMovePieceDownForBestMove(currShape))
			{
				movePieceDownForBestMove(currShape); 
				downCounter++;
				deletePieceOnBoard(currShape); //for next check
			}
		
			downCounters[col] = downCounter;
			placePieceOnBoard(currShape); //because we need to calculate the deleted lines
			removedLinesCounter[col] = checkFullLinesOnBoardForBestMove();
			deletePieceOnBoard(currShape);
		}
		//find optimal move
		int maxRemoved = 0, bestCol = 0, maxDepth = 0;
		for (int i = 0; i < GAME_WIDTH; i++)
			if (removedLinesCounter[i] > maxRemoved)
			{
				maxRemoved = removedLinesCounter[i];
				bestCol = i;
			}

		if (maxRemoved == 0) //if there are no lines removed, let's check max depth
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (downCounters[i] > maxDepth)
				{
					maxDepth = downCounters[i];
					bestCol = i;
				}
			}
		}
		//update roatation arr
		rotationsArr[rotation].downCounter = maxDepth;
		rotationsArr[rotation].linesRemoved = maxRemoved;
		rotationsArr[rotation].col = bestCol;
		rotationsArr[rotation].numOfRotations =rotation;
	}
	//look for the best move between rotations
	int  maxOfMaxesDepths = 0, maxOfMaxesRemoves = 0;
	int bestOfBestPosRotation=0;
	for (int i = 0; i < GameConfig::NUM_OF_ROTATIONS; i++)
	{
		if (rotationsArr[i].linesRemoved > maxOfMaxesRemoves)
		{
			maxOfMaxesRemoves = rotationsArr[i].linesRemoved;
			bestOfBestPosRotation = i;
		}

	}
	if (maxOfMaxesRemoves == 0) {
		for (int i = 0; i < GameConfig::NUM_OF_ROTATIONS; i++)
		{
			if (rotationsArr[i].downCounter > maxOfMaxesDepths)
			{
				maxOfMaxesDepths = rotationsArr[i].downCounter;
				bestOfBestPosRotation = i;
			}

		}
	}
	deletePieceOnBoard(currShape);	//delete the last check
	currShape = currShapeSaver;
	placePieceOnBoard(currShape);
	setBestMoveTrack(rotationsArr[bestOfBestPosRotation].col, rotationsArr[bestOfBestPosRotation].downCounter, rotationsArr[bestOfBestPosRotation].numOfRotations);
	setLeftRightMoves();			//for best move 
	currShape = currShapeSaver;		//return shape to original position

}

//This function updates the curr track left and right 
void Computer::setLeftRightMoves() {

	if (currTrack.numOfRotations > 0) {
		for(int i=0;i< currTrack.numOfRotations;i++)
			currShape.rotatePieceClockwise();
	}
	int minX= currShape.getShape()[0].getX();
	for (int i = 1; i < shape::NUM_OF_POINTS; i++)
	{
		if (minX > currShape.getShape()[i].getX())
			minX = currShape.getShape()[i].getX();
	}
	int diffX =minX - currTrack.col; 
	int i = 0;
	currTrack.right = currTrack.left = 0;
	if (diffX < 0)
	{
		diffX = -diffX;
		currTrack.right=diffX;
	}
	else
	{
		currTrack.left = diffX;
	}
}

//This function is checking if piece can go down for best move 
bool Computer::checkMovePieceDownForBestMove(const shape& s) const 
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		tmp.set(tmp.getX(), tmp.getY() + 1);//to check the next line 
		if ((getCoordInBoard(tmp) != 0) || (tmp.getY() >= GAME_HEIGHT))
			return false;
	}
	return true;
}

//This function is updating curr track
void Computer::setBestMoveTrack(int col,int down, int rotate) 
{
	currTrack.col = col;
	currTrack.downCounter = down;
	currTrack.numOfRotations = rotate;
}

//This function is checking if the shape can move left, right or rotate if so it moves it
void Computer::movePieceLeftRightForBestMove(char keyPressed, shape& s){

	deletePieceOnBoard(s);											//Remove shape from matrix
	s.move(keyPressed);														//Moving the curr shape
	placePieceOnBoard(s);													//putting the coordinates in matrix
}

//This function gets a shape, checks if its possible to move it down on the screen and on the matrix and if so it moves it
void Computer::movePieceDownForBestMove(shape& s)
{
	deletePieceOnBoard(s);															//Delete shape from matrix

	for (int i = 0; i < shape::NUM_OF_POINTS; i++)												//Moving curr shape
	{
		s.getShape()[i].movePointDown();
	}
	placePieceOnBoard(s);
}

//This function calculates a random move for different computer modes
void Computer::calcRandomMove()
{
	int randomIndex = rand() % (GameConfig::NUM_OF_DIRECTIONS);

	switch (randomIndex) {
	case RANDOM0: 
		currMove =(char) GameConfig::eKeys_left::LEFT; 
		break;
	case RANDOM1: 
		currMove =(char) GameConfig::eKeys_left::RIGHT;
		break;
	case RANDOM2:
		currMove = (char)GameConfig::eKeys_left::ROTATE_clockwise; 
		break;
	case RANDOM3: 
		currMove = (char)GameConfig::eKeys_left::ROTATE_counter;
		break;
	case RANDOM4: 
		currMove = (char)GameConfig::eKeys_left::DROP; 
		break;
	}

}

//This function is executes the curr move on the board
void Computer::calcMove(char keyPressed)
{
	movesCounter++;
	if (gameMode == GOOD && movesCounter == GOOD_RANDOM_MOVE)
	{
		calcRandomMove();
		movesCounter = 0;

	}

	else if (gameMode == NOVICE && movesCounter == NOVICE_RANDOM_MOVE)
	{
		calcRandomMove();
		movesCounter = 0;
	}

	else if (currTrack.numOfRotations > 0) {
		currMove = (char)GameConfig::eKeys_left::ROTATE_clockwise;
		currTrack.numOfRotations--;
	}
	else if (currTrack.left > 0)
	{
		currMove = (char)GameConfig::eKeys_left::LEFT;
		currTrack.left--;
	}
	else if (currTrack.right > 0)
	{
		currMove = (char)GameConfig::eKeys_left::RIGHT;
		currTrack.right--;
	}
	else {
		currMove = (char)GameConfig::eKeys_left::DROP;
	}
}

//This function is moving and then checking if the curr move was a rotation and fixes it if its out of board
void Computer::move()
{
	moveForComputer(currMove);										//move piece
	if(currMove== (char)GameConfig::eKeys_left::ROTATE_clockwise)
		if (!checkIfShapeOnBoard(currShape))
		{
			int min = 0;
			for (int i = 0; i < shape::NUM_OF_POINTS; i++) {//find min y when rotating
				if (min > currShape.getShape()[i].getY())
					min = currShape.getShape()[i].getY();
			}
			int diffY = -min;
			for (int i = 0; i < diffY; i++)
				moveForComputer(shape::MOVE_DOWN);
		}
}

//This function is for moving the pieces on the board
void Computer::moveForComputer(char keyPressed)
{
	if (checkAndMovePieceDown())																		//Moving down
	{
		if (keyPressed == GameConfig::eKeys_right::DROP || keyPressed == GameConfig::eKeys_left::DROP)	//If the key pressed is drop
			checkAndMovePieceDown();
		else if (keyPressed != shape::MOVE_DOWN)																		//Any other key pressed
			movePieceLeftRight(keyPressed);
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

//This function is checking if shape can move left right or roatae for the best move
bool Computer::checMoveForLeftRightForBestMove(const shape& s) const
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		tmp.set(tmp.getX()+1, tmp.getY());
		if (isPointOnBoard(tmp) == false)
			return false;
	}
	return true;
}

//This function is checking number of full lines for best move
int Computer::checkFullLinesOnBoardForBestMove() const
{
	int linesRemoved = 0;
	for (int rows = Computer::GAME_HEIGHT - 1; rows >= 0; rows--)	//Here we look for a full line
	{
		bool isFull = true;
		for (int cols = 0; cols < (Computer::GAME_WIDTH) && (isFull); cols++)
		{
			if (board[rows][cols] == 0)
				isFull = false;
		}

		if (isFull)
			linesRemoved++;
	}
	return linesRemoved;
}
