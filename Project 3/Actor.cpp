#include "Actor.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// WALL Implementations
bool Wall::canBeDamaged(){return false;}
bool Wall::canBeInfected(){return false;}
bool Wall::canBlockOthers(){return true;}
bool Wall::canBlockFlames(){return true;}
void Wall::doSomething(){}

// PENELOPE Implementations
bool Penelope::canBeDamaged(){return true;}
bool Penelope::canBeInfected(){return true;}
bool Penelope::canBlockOthers(){return true;}
bool Penelope::canBlockFlames(){return false;}
void Penelope::doSomething()
{
	double curX = getX();
	double curY = getY();
	int ch;
	if (sw->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);
			//check to make sure there's no wall
			moveTo(curX - 4, curY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			//check to make sure there's no wall
			moveTo(curX + 4, curY);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			//check to make sure there's no wall
			moveTo(curX, curY + 4);
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			//check to make sure there's no wall
			moveTo(curX, curY - 4);
			break;
		}
	}
}
