#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
#include "Actor.h"

// WALL Implementations
bool Wall::canBeDamaged(){return false;}
bool Wall::canBeInfected(){return false;}
bool Wall::canBlockOthers(){return true;}
bool Wall::canBlockFlames(){return true;}
void Wall::doSomething(){}

