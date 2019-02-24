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
void Actor::dieByFallOrBurnIfAppropriate()
{/*to do*/}
void Actor::beVomitedOnIfAppropriate()
{/*to do*/}
void Actor::pickUpGoodieIfAppropriate(Goodie* g)
{/*to do*/}
bool Actor::blocksMovement() const { return false; }
bool Actor::blocksFlame() const { return false; }
bool Actor::triggersZombieVomit() const { return false; }
bool Actor::triggersOnlyActiveLandmines() const { return false; }


// WALL Implementations
Wall::Wall(StudentWorld* w, double x, double y)
	: Actor(w, IID_WALL, x, y, right, 0)
{}
void Wall::doSomething() {}
bool Wall::blocksMovement() const { return true; }
bool Wall::blocksFlame() const { return true; }


// ACTIVATING OBJECT Implementations
ActivatingObject::ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir)
	: Actor(w, imageID, x, y, dir, depth)
{}


// EXIT Implementations
Exit::Exit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_EXIT, x, y, 1, right)
{}
void Exit::doSomething() 
{/*to do*/}
void Exit::activateIfAppropriate(Actor* a) 
{/*to do*/}
bool Exit::blocksFlame() const { return true; }


// PIT Implementations
Pit::Pit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_PIT, x, y, 0, right)
{}
void Pit::doSomething()
{/*to do*/}
void Pit::activateIfAppropriate(Actor* a)
{/*to do*/}


// FLAME Implementations
Flame::Flame(StudentWorld* w, double x, double y, int dir)
	: ActivatingObject(w, IID_FLAME, x, y, 0, right)
{}
void Flame::doSomething()
{/*to do*/}
void Flame::activateIfAppropriate(Actor* a)
{/*to do*/}


// VOMIT Implementations
Vomit::Vomit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_VOMIT, x, y, 0, right)
{}
void Vomit::doSomething()
{/*to do*/}
void Vomit::activateIfAppropriate(Actor* a)
{/*to do*/}


// LANDMINE Implementations
Landmine::Landmine(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_LANDMINE, x, y, 1, right)
{}
void Landmine::doSomething()
{/*to do*/}
void Landmine::activateIfAppropriate(Actor* a)
{/*to do*/}
void Landmine::dieByFallOrBurnIfAppropriate()
{/*to do*/}
int Landmine::safetyTicks() { return sftyTcks; }
void Landmine::decSafetyTicks() { sftyTcks--; }


// GOODIE Implementations
Goodie::Goodie(StudentWorld* w, int imageID, double x, double y)
	: ActivatingObject(w, imageID, x, y, 1, right)
{}
void Goodie::activateIfAppropriate(Actor* a)
{/*to do*/}
void Goodie::dieByFallOrBurnIfAppropriate()
{/*to do*/}


// VACCINE GOODIE Implementations
VaccineGoodie::VaccineGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_VACCINE_GOODIE, x, y)
{}
void VaccineGoodie::doSomething()
{/*to do*/}
//void VaccineGoodie::pickUp(Penelope* p)
//{/*to do*/}


// GAS CAN GOODIE Implementations
GasCanGoodie::GasCanGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_GAS_CAN_GOODIE, x, y)
{}
void GasCanGoodie::doSomething()
{/*to do*/}
//void GasCanGoodie::pickUp(Penelope* p)
//{/*to do*/}


// LANDMINE GOODIE Implementations
LandmineGoodie::LandmineGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_LANDMINE_GOODIE, x, y)
{}
void LandmineGoodie::doSomething()
{/*to do*/}
//void LandmineGoodie::pickUp(Penelope* p)
//{/*to do*/}


// AGENT Implemenatiations
Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir)
	: Actor(w, imageID, x, y, dir, 0)
{} 
bool Agent::blocksMovement() const { return true; }
bool Agent::triggersOnlyActiveLandmines() const { return true; }


// HUMAN Implementations
Human::Human(StudentWorld* w, int imageID, double x, double y)
	: Agent(w, imageID, x, y, right)
{}
void Human::beVomitedOnIfAppropriate()
{/*to do*/ }
bool Human::triggersZombieVomit() const { return true; }
void Human::clearInfection() { infected = false; }
int Human::getInfectionDuration() const { return infectionDuration; }
void Human::infect() { infected = true; }
void Human::incInfectionDuration() { infectionDuration++; }
