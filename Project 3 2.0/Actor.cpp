#include "Actor.h"
#include "StudentWorld.h"

// ACTOR Implementations
Actor::Actor(StudentWorld* w, int imageID, double x, double y, int dir, int depth)
	: GraphObject(imageID, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, dir, depth)
{ sw = w; }
bool Actor::isDead() const { return dead; }
void Actor::setDead() { dead = true; }
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
int ActivatingObject::ticks() { return ticksSinceCreation; }
void ActivatingObject::incTicks() { ticksSinceCreation++; }
//_______________________________________________________________________________________//

// EXIT Implementations
Exit::Exit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_EXIT, x, y, 1, right)
{}
void Exit::doSomething() 
{
	world()->activateOnAppropriateActors(this);
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
{
	world()->activateOnAppropriateActors(this);
}
void Pit::activateIfAppropriate(Actor* a)
{
	a->dieByFallOrBurnIfAppropriate();
}

//_______________________________________________________________________________________//

// FLAME Implementations
Flame::Flame(StudentWorld* w, double x, double y, int dir)
	: ActivatingObject(w, IID_FLAME, x, y, 0, right)
{}
void Flame::doSomething()
{
	if (isDead())
		return;
	else
	{
		incTicks();
		if (ticks() == 2)
		{
			setDead();
			return;
		}
		world()->activateOnAppropriateActors(this);
	}
}
void Flame::activateIfAppropriate(Actor* a)
{
	a->dieByFallOrBurnIfAppropriate();
}

//_______________________________________________________________________________________//

// VOMIT Implementations
Vomit::Vomit(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_VOMIT, x, y, 0, right)
{}
void Vomit::doSomething()
{
	if (isDead())
		return;
	else
	{
		incTicks();
		if (ticks() == 2)
		{
			setDead();
			return;
		}
		world()->activateOnAppropriateActors(this);
	}

}
void Vomit::activateIfAppropriate(Actor* a)
{
	a->beVomitedOnIfAppropriate();
}

//_______________________________________________________________________________________//

// LANDMINE Implementations
Landmine::Landmine(StudentWorld* w, double x, double y)
	: ActivatingObject(w, IID_LANDMINE, x, y, 1, right)
{}
void Landmine::doSomething()
{/*to do*/}
void Landmine::activateIfAppropriate(Actor* a)
{
	if (isDead())
		return;

}
void Landmine::dieByFallOrBurnIfAppropriate()
{
	// When another flame overlaps with a landmine it will trigger the landmine 
	// and cause it to introduce flames all around the landmine.
}
int Landmine::safetyTicks() { return sftyTcks; }
void Landmine::decSafetyTicks() { sftyTcks--; }
//_______________________________________________________________________________________//

// GOODIE Implementations
Goodie::Goodie(StudentWorld* w, int imageID, double x, double y)
	: ActivatingObject(w, imageID, x, y, 1, right)
{}
void Goodie::activateIfAppropriate(Actor* a)
{
	a->pickUpGoodieIfAppropriate(this);
}
void Goodie::dieByFallOrBurnIfAppropriate()
{
	setDead();
}

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
		world()->activateOnAppropriateActors(this);
	}
}
void VaccineGoodie::pickUp(Penelope* p)
{
	world()->increaseScore(50);
	setDead();
	world()->playSound(SOUND_GOT_GOODIE);
	p->increaseVaccines();
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
		world()->activateOnAppropriateActors(this);
	}
}
void GasCanGoodie::pickUp(Penelope* p)
{
	world()->increaseScore(50);
	setDead();
	world()->playSound(SOUND_GOT_GOODIE);
	for(int i = 0; i < 5; i++)
		p->increaseFlameCharges();
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
		world()->activateOnAppropriateActors(this);
	}
}
void LandmineGoodie::pickUp(Penelope* p)
{
	world()->increaseScore(50);
	setDead();
	world()->playSound(SOUND_GOT_GOODIE);
	p->increaseLandmines();
	p->increaseLandmines();
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
	infect();
	world()->playSound(SOUND_CITIZEN_INFECTED);
}
bool Human::triggersZombieVomit() const { return true; }
void Human::clearInfection() { infected = false; }
void Human::infect() { infected = true; }
bool Human::isInfected() { return infected; }
int Human::infectionTime() { return infectionDuration; }
void Human::incInfectionDuration() 
{ 
	infectionDuration++; 
}

//_______________________________________________________________________________________//

// PENELOPE Implementations
Penelope::Penelope(StudentWorld* w, double x, double y)
	: Human(w, IID_PLAYER, x, y)
{}
void Penelope::doSomething()
{
	if (isInfected())
		incInfectionDuration();
	if (infectionTime() == 500)
	{
		setDead();
		world()->playSound(SOUND_PLAYER_DIE);
	}

	//to do

	int ch;
	double curX = getX();
	double curY = getY();
	if (world()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
		{
			setDirection(left);
			if (world()->isAgentMovementBlockedAt(curX - 4, curY))
				break;
			else
				moveTo(curX - 4, curY);
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			setDirection(right);
			if (world()->isAgentMovementBlockedAt(curX + 4, curY))
				break;
			else
				moveTo(curX + 4, curY);
			break;
		}
		case KEY_PRESS_UP:
		{
			setDirection(up);
			if (world()->isAgentMovementBlockedAt(curX, curY + 4))
				break;
			else
				moveTo(curX, curY + 4);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			setDirection(down);
			if (world()->isAgentMovementBlockedAt(curX, curY - 4))
				break;
			else
				moveTo(curX, curY - 4);
			break;
		}
		}
	}
}
void Penelope::useExitIfAppropriate()
{
	if (world()->numCitizens() == 0)
	{
		world()->recordLevelFinishedIfAllCitizensGone();
	}
}
void Penelope::dieByFallOrBurnIfAppropriate()
{
	setDead();
}
void Penelope::pickUpGoodieIfAppropriate(Goodie* g)
{
	g->pickUp(this);
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
	world()->increaseScore(500);
	setDead();
	world()->recordCitizenGone();
	world()->playSound(SOUND_CITIZEN_SAVED);
}
void Citizen::dieByFallOrBurnIfAppropriate()
{
	world()->increaseScore(-1000);
	setDead();
	world()->recordCitizenGone();
	world()->playSound(SOUND_CITIZEN_DIE);
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
void DumbZombie::doSomething()
{
	int dir = getDirection();
	double curX = getX();
	double curY = getY();
	switch (dir)
	{
	case left:
	{
		if (world()->isZombieVomitTargetAt(curX - SPRITE_WIDTH, curY))
			new Vomit(world(), curX - SPRITE_WIDTH, curY);
	}
	case right:
	{
		if (world()->isZombieVomitTargetAt(curX + SPRITE_WIDTH, curY))
			new Vomit(world(), curX + SPRITE_WIDTH, curY);
	}
	case up:
	{
		if (world()->isZombieVomitTargetAt(curX, curY + SPRITE_HEIGHT))
			new Vomit(world(), curX, curY + SPRITE_HEIGHT);
	}
	case down:
	{
		if (world()->isZombieVomitTargetAt(curX, curY - SPRITE_HEIGHT))
			new Vomit(world(), curX, curY - SPRITE_HEIGHT);
	}
	}

	// TO DO
}
void DumbZombie::dieByFallOrBurnIfAppropriate()
{
	setDead();
	world()->increaseScore(1000);
}

//_______________________________________________________________________________________//

// SMART ZOMBIE Implementations
SmartZombie::SmartZombie(StudentWorld* w, double x, double y)
	: Zombie(w, x, y)
{}
void SmartZombie::doSomething()
{
	//to do
}
void SmartZombie::dieByFallOrBurnIfAppropriate()
{
	setDead();
	world()->increaseScore(2000);
}