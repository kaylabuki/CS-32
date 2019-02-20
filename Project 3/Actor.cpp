#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// WALL Implementations
bool Wall::canBeDamaged() { return false; }
bool Wall::canBeInfected() { return false; }
bool Wall::canBlockOthers() { return true; }
bool Wall::canBlockFlames() { return true; }
void Wall::doSomething() {}

// PENELOPE Implementations
bool Penelope::canBeDamaged() { return true; }
bool Penelope::canBeInfected() { return true; }
bool Penelope::canBlockOthers() { return true; }
bool Penelope::canBlockFlames() { return false; }
bool Penelope::isPenelope() { return true; }
void Penelope::doSomething()
{
	double curX = getX();
	double curY = getY();
	int ch;
	if (getSW()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (getSW()->getContents(curX - 4, curY) == "wall")
				break;
			moveTo(curX - 4, curY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (getSW()->getContents(curX + 4, curY) == "wall")
				break;
			moveTo(curX + 4, curY);
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (getSW()->getContents(curX, curY + 4) == "wall")
				break;
			moveTo(curX, curY + 4);
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (getSW()->getContents(curX, curY - 4) == "wall")
				break;
			moveTo(curX, curY - 4);
			break;
		}
	}
}