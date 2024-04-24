#ifndef __COMPUTER_H
#define __COMPUTER_H

#include <cstdlib>
#include "shape.h"
#include "gameConfig.h"
#include "player.h"


//save best move data for computer
struct bestMove
{
	int linesRemoved;
	int downCounter;
	int col;
	int numOfRotations;
	int left;
	int right;
};

class Computer: public player
{
public:
	Computer(int minX, int color, int playerNum, char choice) :player(minX, color, playerNum)
	{
		currMove = 0;
		gameMode = choice;
		movesCounter = 0;
	};

	void calcRandomMove();
	int checkFullLinesOnBoardForBestMove() const;													//Checking if there are full lines (for the best move calculate)
	virtual void giveMeShape() override;													        //Get new shape
	virtual void calcMove(char keyPressed) override;												//Moving the shape
	void findAndUpdateBestTrack();
	void movePieceLeftRightForBestMove(char keyPressed, shape& s);
	void movePieceDownForBestMove(shape& s);
	void setLeftRightMoves();
	void moveForComputer(char keyPressed);
	virtual void move()override;
	bool checMoveForLeftRightForBestMove(const shape& s) const;
	bool checkMovePieceDownForBestMove(const shape& s) const;
	void setBestMoveTrack(int col, int down, int rotate);
	virtual ~Computer() {};

	static constexpr int BEST = 'a'; //user choice for BEST mode
	static constexpr int GOOD = 'b'; //user choice for GOOD mode
	static constexpr int NOVICE = 'c';  //user choice for NOVICE mode
	static constexpr int GOOD_RANDOM_MOVE = 40; //number of moves until miss, for GOOD mode
	static constexpr int NOVICE_RANDOM_MOVE = 10; //number of moves until miss, for NOVICE mode

	enum {RANDOM0 =0,RANDOM1 =1,RANDOM2 =2,RANDOM3 =3,RANDOM4 =4}; //for generate random move when missing in the computer modes

private:
	bestMove currTrack;
	char currMove;
	char gameMode;
	unsigned int movesCounter;

};

#endif // !__COMPUTER_H