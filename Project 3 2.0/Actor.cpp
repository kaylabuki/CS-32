#include "Actor.h"
#include "StudentWorld.h"

// ACTOR Implementations
Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth)
	: GraphObject(imageID, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, dir, depth)
{ sw = w; }
bool Actor::isDead() const { return alive; }
void Actor::setDead() { alive = false; }
StudentWorld* Actor::world() const { return sw; }
void Actor::activateIfAppropriate(Actor* a) 
{/*to do*/}
void Actor::useExitIfAppropriate()
{/*to do*/}


// WALL Implementations
Wall::Wall(StudentWorld* w, double x, double y)
	: Actor(w, IID_WALL, x, y, right, 0)
{}
void Wall::doSomething() {}
bool Wall::blocksMovement() const { return true; }
bool Wall::blocksFlame() const { return true; }

// EXIT Implementations

// EXIT Implementations

// EXIT Implementations

// EXIT Implementations
Exit::Exit(StudentWorld* w, double x, double y)
: ActivatingObject(w, IID_EXIT, SPRITE_WIDTH * x, SPRITE_WIDTH * y, 1, right) 
{}
