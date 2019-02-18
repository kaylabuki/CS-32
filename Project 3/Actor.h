#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	Actor(int imageId, double startX, double startY, int startDirection, int depth, StudentWorld* theSW)
		: GraphObject(imageId, startX, startY, startDirection, depth, 1.0)
	{
		sw = theSW;
	}
	virtual void doSomething() = 0;
	virtual bool canBeDamaged() = 0;
	virtual bool canBeInfected() = 0;
	virtual bool canBlockOthers() = 0;
	virtual bool canBlockFlames() = 0;
protected:
	StudentWorld* sw;
};

class Wall : public Actor
{
public:
	Wall(StudentWorld* sw)
		: Actor(IID_WALL, SPRITE_WIDTH * level_x,
			SPRITE_WIDTH * level_y, right, 0, sw)
	{}

	virtual void doSomething();
	virtual bool canBeDamaged();
	virtual bool canBeInfected();
	virtual bool canBlockOthers();
	virtual bool canBlockFlames();
};

#endif // ACTOR_H_
