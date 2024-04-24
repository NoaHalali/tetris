#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
#include <iostream>
using std::cout;
using std::cin;

class GameConfig
{
public:

	enum { ESC = 27, EXIT = 9, START_NEW_GAME_HUMAN_VS_HUMAN = 1, START_NEW_GAME_HUMAN_VS_COMPUTER=2, START_NEW_GAME_COMPUTER_VS_COMPUTER=3, CONTINUE = 4, COLORS = 5, INSTRUCTIONS = 8, BLACK = 7 };			//The keys for escape, start, instuctions and colors
	enum class eKeys_left { LEFT = 'A', RIGHT = 'D', ROTATE_clockwise = 'S', ROTATE_counter = 'W', DROP = 'X' };	//The left player key
	enum class eKeys_right { LEFT = 'J', RIGHT = 'L', ROTATE_clockwise = 'K', ROTATE_counter = 'I', DROP = 'M' };	//The right player key
	enum { SLEEP_TIME = 50, LONG_SLEEP_TIME = 2000, AVG_SLEEP = 200 };														//Sleep time

	// Static member function to assign a character from eKeys_left to a char
	static char& assignFromEnum(char& dest, const eKeys_left& src)
	{
		dest = static_cast<char>(src);
		return dest;
	}
	//Overloading two functions for the comparison of the keypressed 
	friend bool operator==(const char key, const eKeys_left& rhs) {				//Left ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}
	friend bool operator==(const char key, const eKeys_right& rhs) {			//Right ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}

	//The proportions where the boards start
	static constexpr int MIN_X_BOARD2 = 31;					//The second board beginning x point
	static constexpr int MIN_X_BOARD1 = 1;					//The first board beginning x point
	static constexpr int MIN_Y = 1;							//Both boards beginning y point
	static constexpr int MID_WIDTH_MATRIX = 5;
	static constexpr int NUM_OF_ROTATIONS = 4;
	static constexpr int NUM_OF_DIRECTIONS = 5;				//The possibble moves for a single shape

	// Colors for the game pieces
	static const int COLORS_ARRAY[];
	static const int NUM_OF_COLORS;

	static constexpr double CHANCES_FOR_REGULAR_SHAPE= 0.95; //because bomb has 0.05 chances						


	static constexpr int LEFT_PLAYER= 1;
	static constexpr int RIGHT_PLAYER= 2;
};

void gotoxy(int, int);
void clrscr();

#endif