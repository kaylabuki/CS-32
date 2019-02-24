#include "Actor.h"
#include "StudentWorld.h"

// ACTOR Implementations
Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth)
	: GraphObject(imageID, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, dir, depth)
{ sw = w; }
bool Actor::isDead() const { return alive; }
void Actor::setDead() { alive = false; }
StudentWorld* Actor::world() const { return sw; }
void Actor::activateIfAppropriate(Actor* a) {}
void Actor::useExitIfAppropriate(){}
void Actor::dieByFallOrBurnIfAppropriate(){}
void Actor::beVomitedOnIfAppropriate(){}
void Actor::pickUpGoodieIfAppropriate(Goodie* g){}
bool Actor::blocksMovement() const { return false; }
bool Actor::blocksFlame() const { return false; }
bool Actor::triggersZombieVomit() const { return false; }
bool Actor::triggersOnlyActiveLandmines() const { return false; }

//_______________________________________________________________________________________//

// WALL Implementations
Wall::Wall(StudentWorld* w, double x, double y)
	: Actor(w, IID_WALL, x, y, right, 0)
{}
void Wall::doSomething() {}
bool Wall::blocksMovement() const { return true; }
bool Wall::blocksFlame() const { return true; }

//_______________________________________________________________________________________//

// ACTIVATING OBJECT Implementations
ActivatingObject::ActivatingObject(StudentWorld* w, int imageID, double x, double y, int depth, int dir)
	: Actor(w, imageID, x, y, dir, depth)
{}

//_______________________________________________________________________________________//

// EXIT Implementations
Exit::Exit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_EXIT, x, y, 1, right)
{}
void Exit::doSomething() 
{
	world()->activateOnAppropriateActors(this);
	// to do
}
void Exit::activateIfAppropriate(Actor* a) 
{
	a->useExitIfAppropriate();
}
bool Exit::blocksFlame() const { return true; }

//_______________________________________________________________________________________//

// PIT Implementations
Pit::Pit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_PIT, x, y, 0, right)
{}
void Pit::doSomething()
{/*to do*/}
void Pit::activateIfAppropriate(Actor* a)
{/*to do*/}

//_______________________________________________________________________________________//

// FLAME Implementations
Flame::Flame(StudentWorld* w, double x, double y, int dir)
	: ActivatingObject(w, IID_FLAME, x, y, 0, right)
{}
void Flame::doSomething()
{/*to do*/}
void Flame::activateIfAppropriate(Actor* a)
{/*to do*/}

//_______________________________________________________________________________________//

// VOMIT Implementations
Vomit::Vomit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_VOMIT, x, y, 0, right)
{}
void Vomit::doSomething()
{/*to do*/}
void Vomit::activateIfAppropriate(Actor* a)
{/*to do*/}

//_______________________________________________________________________________________//

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

//_______________________________________________________________________________________//

// GOODIE Implementations
Goodie::Goodie(StudentWorld* w, int imageID, double x, double y)
	: ActivatingObject(w, imageID, x, y, 1, right)
{}
void Goodie::activateIfAppropriate(Actor* a)
{/*to do*/}
void Goodie::dieByFallOrBurnIfAppropriate()
{/*to do*/}

//_______________________________________________________________________________________//

// VACCINE GOODIE Implementations
VaccineGoodie::VaccineGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_VACCINE_GOODIE, x, y)
{}
void VaccineGoodie::doSomething()
{
	if (isDead())
		return;
	else
	{
		//to do
	}
}
void VaccineGoodie::pickUp(Penelope* p)
{
	//to do
}

//_______________________________________________________________________________________//

// GAS CAN GOODIE Implementations
GasCanGoodie::GasCanGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_GAS_CAN_GOODIE, x, y)
{}
void GasCanGoodie::doSomething()
{
	if (isDead())
		return;
	else
	{
		//to do
	}
}
void GasCanGoodie::pickUp(Penelope* p)
{
	// to do
}

//_______________________________________________________________________________________//

// LANDMINE GOODIE Implementations
LandmineGoodie::LandmineGoodie(StudentWorld* w, double x, double y)
	: Goodie(w, IID_LANDMINE_GOODIE, x, y)
{}
void LandmineGoodie::doSomething()
{
	if (isDead())
		return;
	else
	{
		//to do
	}
}
void LandmineGoodie::pickUp(Penelope* p)
{
	//to do
}

//_______________________________________________________________________________________//

// AGENT Implemenatiations
Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir)
	: Actor(w, imageID, x, y, dir, 0)
{} 
bool Agent::blocksMovement() const { return true; }
bool Agent::triggersOnlyActiveLandmines() const { return true; }

//_______________________________________________________________________________________//

// HUMAN Implementations
Human::Human(StudentWorld* w, int imageID, double x, double y)
	: Agent(w, imageID, x, y, right)
{}
void Human::beVomitedOnIfAppropriate()
{
	//to do 
}
bool Human::triggersZombieVomit() const { return true; }
void Human::clearInfection() { infected = false; }
int Human::getInfectionDuration() const { return infectionDuration; }
void Human::infect() { infected = true; }
void Human::incInfectionDuration() { infectionDuration++; }

//_______________________________________________________________________________________//

// PENELOPE Implementations
Penelope::Penelope(StudentWorld* w, double x, double y)
	: Human(w, IID_PLAYER, x, y)
{}
void Penelope::doSomething()
{
	//to do
}
void Penelope::useExitIfAppropriate()
{
	//to do
}
void Penelope::dieByFallOrBurnIfAppropriate()
{
	//to do
}
void Penelope::pickUpGoodieIfAppropriate(Goodie* g)
{
	//to do
}
void Penelope::increaseVaccines() { vaccines++; }
void Penelope::increaseFlameCharges() { flameCharges++; }
void Penelope::increaseLandmines() { landmines++; }
int Penelope::getNumVaccines() const { return vaccines; }
int Penelope::getNumFlameCharges() const { return flameCharges; }
int Penelope::getNumLandmines() const { return landmines; }

//_______________________________________________________________________________________//

// CITIZEN Implementations
Citizen::Citizen(StudentWorld* w, double x, double y)
	: Human(w, IID_CITIZEN, x, y)
{}
void Citizen::doSomething()
{
	//to do
}
void Citizen::useExitIfAppropriate()
{
	//to do
}
void Citizen::dieByFallOrBurnIfAppropriate()
{
	//to do
}

//_______________________________________________________________________________________//

// ZOMBIE Implementations

Zombie::Zombie(StudentWorld* w, double x, double y)
	: Agent(w, IID_ZOMBIE, x, y, right)
{}


//_______________________________________________________________________________________//

// DUMB ZOMBIE Implementations
DumbZombie::DumbZombie(StudentWorld* w, double x, double y)
	: Zombie(w, x, y)
{}
void DumbZombie::doSomeThing()
{
	//to do
}
void DumbZombie::dieByFallOrBurnIfAppropriate()
{
	//to do
}

//_______________________________________________________________________________________//

// SMART ZOMBIE Implementations
SmartZombie::SmartZombie(StudentWorld* w, double x, double y)
	: Zombie(w, x, y)
{}
void SmartZombie::doSomeThing()
{
	//to do
}
void SmartZombie::dieByFallOrBurnIfAppropriate()
{
	//to do
}