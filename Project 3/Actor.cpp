#include "Actor.h"
#include "StudentWorld.h"

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
	//to do
}
