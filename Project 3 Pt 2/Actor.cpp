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
void Penelope::doSomething()
{
	int ch;
	if (getSW()->getKey(ch))
	{
		cout << "(" << getX() << ", " << getY() << endl;
		switch (ch)
		{
		case KEY_PRESS_LEFT:
		{
			setDirection(left);
			if (getSW()->blocked(getX() - 4, getY()))
				break;
			else
				moveTo(getX() - 4, getY());
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			setDirection(right);
			if(getSW()->blocked(getX() + 4, getY()))
				break;
			else
				moveTo(getX() + 4, getY());
			break;
		}
		case KEY_PRESS_UP:
		{
			setDirection(up);
			if (getSW()->blocked(getX(), getY() + 4))
				break;
			else
				moveTo(getX(), getY() + 4);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			setDirection(down);
			if (getSW()->blocked(getX(), getY() - 4))
				break;
			else
				moveTo(getX(), getY() - 4);
			break;
		}
		}
	}
}
