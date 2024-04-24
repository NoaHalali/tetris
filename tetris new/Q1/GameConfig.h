#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:

	enum { ESC = 27, EXIT = 9, START_NEW_GAME=1, CONTINUE=2, COLORS=3, INSTRUCTIONS=8};			//the key for escape
	enum class eKeys_left { LEFT = 'A', RIGHT = 'D', ROTATE_clockwise = 'S', ROTATE_counter = 'W', DROP = 'X' };
	enum class eKeys_right { LEFT = 'J', RIGHT = 'L', ROTATE_clockwise = 'K', ROTATE_counter = 'I', DROP = 'M' };

	// Static member function to assign a character from eKeys_left to a char
	static char& assignFromEnum(char& dest, const eKeys_left& src)
	{
		dest = static_cast<char>(src);
		return dest;
	}
	//overloading two functions for the comparison of the keypressed 
	friend bool operator==(const char key, const eKeys_left& rhs) {				//left ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}
	friend bool operator==(const char key, const eKeys_right& rhs) {			//right ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}

	//the proportions where the boards start
	static constexpr int MIN_X_BOARD2 = 31;					//the second board beginning x point
	static constexpr int MIN_X_BOARD1 = 1;					//the first board beginning x point
	static constexpr int MIN_Y = 1;							//both boards beginning y point
						

};

void gotoxy(int, int);
void clrscr();

#endif