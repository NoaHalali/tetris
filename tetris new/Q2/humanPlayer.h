
#ifndef __HUMANPLAYER_H
#define __HUMANPLAYER

#include "player.h"

class humanPlayer: public player
{
public:
	humanPlayer(int minX, int color,int playerNum) :player(minX, color, playerNum) {};
	virtual void giveMeShape() override;										//Get new shape
	virtual void move() override;												//Moving the shape
	virtual void calcMove(char keyPressed) override;								
	virtual ~humanPlayer() {};
};
#endif

