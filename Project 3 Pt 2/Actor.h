#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <list>
using namespace std;
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	Actor(int imageId, double startX, double startY, int startDirection, int depth, StudentWorld* theSW)
		: GraphObject(imageId, startX, startY, startDirection, depth)
	{
		sw = theSW;
	}
	virtual void doSomething() = 0;
	virtual bool canBeDamaged() = 0;
	virtual bool canBeInfected() = 0;
	virtual bool canBlockOthers() = 0;
	virtual bool canBlockFlames() = 0;
	virtual bool isWall() = 0; //DELETE!
	bool alive() { return lifeStatus; }
	void setAlive(bool set) { lifeStatus = set; }
	StudentWorld* getSW(){return sw;}
private:
	StudentWorld* sw;
	bool lifeStatus;
};

class Wall : public Actor
{
public:
	Wall(StudentWorld* sw, double level_x, double level_y)
		: Actor(IID_WALL, SPRITE_WIDTH * level_x,
			SPRITE_WIDTH * level_y, right, 0, sw)
	{}

	virtual void doSomething();
	virtual bool canBeDamaged();
	virtual bool canBeInfected();
	virtual bool canBlockOthers();
	virtual bool canBlockFlames();
	virtual bool isWall() { return true; } //DELETE!
};

class Penelope : public Actor
{
public:
	Penelope(StudentWorld* sw, double level_x, double level_y)
		: Actor(IID_PLAYER, SPRITE_WIDTH * level_x,
			SPRITE_WIDTH * level_y, right, 0, sw)
	{}

	virtual void doSomething();
	virtual bool canBeDamaged();
	virtual bool canBeInfected();
	virtual bool canBlockOthers();
	virtual bool canBlockFlames();
	virtual bool isWall() { return false; } // DELETE!
private:
	//list<*Goodies> goodies; //to be used for part 2
	bool infected = false;
	int infectionCount = 0;
};


#endif // ACTOR_H_