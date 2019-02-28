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
bool Actor::threatensCitizens() const { return false; }
bool Actor::triggersCitizens() const { return false; }

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
{
	if (isDead())
		return;
	decSafetyTicks();
	if (safetyTicks() > 0)
		return;
	setDead();
	world()->playSound(SOUND_LANDMINE_EXPLODE);
	world()->activateOnAppropriateActors(this);
	double curX = getX();
	double curY = getY();
	Actor* p = new Flame(world(), curX, curY, right);
	Actor* w = new Flame(world(), curX - SPRITE_WIDTH, curY, right);
	Actor* e = new Flame(world(), curX + SPRITE_WIDTH, curY, right);
	Actor* s = new Flame(world(), curX, curY - SPRITE_HEIGHT, right);
	Actor* n = new Flame(world(), curX, curY + SPRITE_HEIGHT, right);
	Actor* nw = new Flame(world(), curX - SPRITE_WIDTH, curY + SPRITE_HEIGHT, right);
	Actor* ne = new Flame(world(), curX + SPRITE_WIDTH, curY + SPRITE_HEIGHT, right);
	Actor* sw = new Flame(world(), curX - SPRITE_WIDTH, curY - SPRITE_HEIGHT, right);
	Actor* se = new Flame(world(), curX + SPRITE_WIDTH, curY - SPRITE_HEIGHT, right);
	world()->addActor(p);
	world()->addActor(w);
	world()->addActor(e);
	world()->addActor(s);
	world()->addActor(n);
	world()->addActor(nw);
	world()->addActor(ne);
	world()->addActor(sw);
	world()->addActor(se);
}
void Landmine::activateIfAppropriate(Actor* a)
{
	a->dieByFallOrBurnIfAppropriate();
}
void Landmine::dieByFallOrBurnIfAppropriate()
{
	while (safetyTicks() != 0)
		decSafetyTicks();
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
	world()->playSound(SOUND_GOT_GOODIE);
	p->increaseVaccines();
	setDead();
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
		world()->activateOnAppropriateActors(this);
}
void GasCanGoodie::pickUp(Penelope* p)
{
	world()->increaseScore(50);
	world()->playSound(SOUND_GOT_GOODIE);
	for(int i = 0; i < 5; i++)
		p->increaseFlameCharges();
	setDead();
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
	world()->playSound(SOUND_GOT_GOODIE);
	p->increaseLandmines();
	p->increaseLandmines();
	setDead();
}

//_______________________________________________________________________________________//

// AGENT Implemenatiations
Agent::Agent(StudentWorld* w, int imageID, double x, double y, int dir)
	: Actor(w, imageID, x, y, dir, 0)
{} 
bool Agent::blocksMovement() const { return true; }
bool Agent::triggersOnlyActiveLandmines() const { return true; }
int Agent::ticks() { return ticksSinceCreation; }
void Agent::incTicks() { ticksSinceCreation++; }

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
			if (world()->isAgentMovementBlockedAt(curX - 4, curY, this))
				break;
			else
				moveTo(curX - 4, curY);
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			setDirection(right);
			if (world()->isAgentMovementBlockedAt(curX + 4, curY, this))
				break;
			else
				moveTo(curX + 4, curY);
			break;
		}
		case KEY_PRESS_UP:
		{
			setDirection(up);
			if (world()->isAgentMovementBlockedAt(curX, curY + 4, this))
				break;
			else
				moveTo(curX, curY + 4);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			setDirection(down);
			if (world()->isAgentMovementBlockedAt(curX, curY - 4, this))
				break;
			else
				moveTo(curX, curY - 4);
			break;
		}
		case KEY_PRESS_TAB:
		{
			if (getNumLandmines() > 0)
			{
				decreaseLandmines();
				Actor* landmine  = new Landmine(world(), getX(), getY());
				world()->addActor(landmine);
			}
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
void Penelope::decreaseVaccines() { vaccines--; }
void Penelope::decreaseFlameCharges() { flameCharges--; }
void Penelope::decreaseLandmines() { landmines--; }
int Penelope::getNumVaccines() const { return vaccines; }
int Penelope::getNumFlameCharges() const { return flameCharges; }
int Penelope::getNumLandmines() const { return landmines; }
bool Penelope::triggersCitizens() const { return true; }

//_______________________________________________________________________________________//

// CITIZEN Implementations
Citizen::Citizen(StudentWorld* w, double x, double y)
	: Human(w, IID_CITIZEN, x, y)
{}
void Citizen::doSomething()
{
	if (isDead())
		return;
	if (isInfected())
		incInfectionDuration();
	if (infectionTime() == 500)
	{
		setDead();
		world()->playSound(SOUND_ZOMBIE_BORN);
		world()->increaseScore(-1000);
		int zombieChance = randInt(1, 10);
		if (zombieChance > 3)
		{
			DumbZombie* dz = new DumbZombie(world(), getX(), getY());
			world()->addActor(dz);
			return;
		}
		else
		{
			SmartZombie* sz = new SmartZombie(world(), getX(), getY());
			world()->addActor(sz);
			return;
		}
	}

	if (ticks() % 2 == 0)
		return;

	double dist_pX;
	double dist_pY;
	double dist_p;
	double dist_zX;
	double dist_zY;
	double dist_z;


	double x;
	double y;
	double dist;
	bool isZombie;
	world()->locateNearestCitizenTrigger(getX(), getY(), x, y, dist, isZombie);
	if (isZombie)
	{
		dist_pX = getX() - world()->getPen()->getX();
		dist_pY = getY() - world()->getPen()->getY();
		
		dist_p = sqrt((dist_pX * dist_pX) + (dist_pY * dist_pY));
		dist_z = dist;
	}
	else
	{
		world()->locateNearestCitizenThreat(getX(), getY(), x, y, dist);

		dist_zX = getX() - x;
		dist_zY = getY() - y;

		dist_z = sqrt((dist_zX * dist_zX) + (dist_zY * dist_zY));
		dist_p = dist;
	}

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
void Zombie::attemptVomit()
{
	int dir = getDirection();
	double curX = getX();
	double curY = getY();
	double vomitX = curX;
	double vomitY = curY;
	switch (dir)
	{
	case left:
	{
		vomitX -= SPRITE_WIDTH;
		break;
	}
	case right:
	{
		vomitX += SPRITE_WIDTH;
		break;
	}
	case up:
	{
		vomitY += SPRITE_HEIGHT;
		break;
	}
	case down:
	{
		vomitY -= SPRITE_HEIGHT;
		break;
	}
	}

	int vomitRand = randInt(1, 3);
	/*if (world()->isZombieVomitTargetAt(vomitX, vomitY))
		cout << "target!" << endl;*/
	if (world()->isZombieVomitTargetAt(vomitX, vomitY) && vomitRand == 1)
	{
		Actor* vomit = new Vomit(world(), vomitX / 16, vomitY / 16);
		world()->addActor(vomit);
		world()->playSound(SOUND_ZOMBIE_VOMIT);
		return;
	}
}
int Zombie::movementPlan() { return movementPlanDist; }
void Zombie::setMovementPlan(int newMovementPlan) { movementPlanDist = newMovementPlan; }
bool Zombie::threatensCitizens() const { return true; }
bool Zombie::triggersCitizens() const { return true; }
//_______________________________________________________________________________________//

// DUMB ZOMBIE Implementations
DumbZombie::DumbZombie(StudentWorld* w, double x, double y)
	: Zombie(w, x, y)
{}
void DumbZombie::doSomething()
{
	if (isDead())
		return;
	incTicks();
	if (ticks() % 2 == 0)
		return;

	attemptVomit();

	double dest_X = getX();
	double dest_Y = getY();
	int newDir = getDirection();

	if (movementPlan() == 0)
	{
		int newMovementPlan = randInt(3, 10);
		setMovementPlan(newMovementPlan);
		newDir = randInt(1, 4);
	}
	
	switch (newDir) {
		case 1:
		case left:
		{
			setDirection(left);
			dest_X--;
			break;
		}
		case 2:
		case right:
		{
			setDirection(right);
			dest_X++;
			break;
		}
		case 3:
		case up:
		{
			setDirection(up);
			dest_Y++;
			break;
		}
		case 4:
		case down:
		{
			setDirection(down);
			dest_Y--;
			break;
		}
	}

	if (!(world()->isAgentMovementBlockedAt(dest_X, dest_Y, this)))
	{
		moveTo(dest_X, dest_Y);
		setMovementPlan(movementPlan() - 1);
	}
	else
		setMovementPlan(0);
}
void DumbZombie::dieByFallOrBurnIfAppropriate()
{
	setDead();
	world()->playSound(SOUND_ZOMBIE_DIE);
	world()->increaseScore(1000);
}

//_______________________________________________________________________________________//

// SMART ZOMBIE Implementations
SmartZombie::SmartZombie(StudentWorld* w, double x, double y)
	: Zombie(w, x, y)
{}
void SmartZombie::doSomething()
{
	if (isDead())
		return;
	incTicks();
	if (ticks() % 2 == 0)
		return;

	attemptVomit();

	double dest_X = getX();
	double dest_Y = getY();
	int newDir = getDirection();

	if (movementPlan() == 0)
	{
		int newMovementPlan = randInt(3, 10);
		setMovementPlan(newMovementPlan);
	}

	double otherX;
	double otherY;
	double distance;
	if (world()->locateNearestVomitTrigger(getX(), getY(), otherX, otherY, distance))
	{
		if (distance > 80)
			newDir = randInt(1, 4);
		else
		{
			if (getX() - otherX == 0)
			{
				if (getY() - otherY < 0)
					newDir = up;
				else
					newDir = down;
			}
			else if (getY() - otherY == 0)
			{
				if (getX() - otherX < 0)
					newDir = right;
				else
					newDir = left;
			}
			else
			{
				int horzOrVert = randInt(1, 2);
				if (horzOrVert == 1)
				{
					if (getX() - otherX < 0)
						newDir = right;
					else
						newDir = left;
				}
				else
				{
					if (getY() - otherY < 0)
						newDir = up;
					else
						newDir = down;
				}
			}
		}
	}

	switch (newDir) {
	case 1:
	case left:
	{
		setDirection(left);
		dest_X--;
		break;
	}
	case 2:
	case right:
	{
		setDirection(right);
		dest_X++;
		break;
	}
	case 3:
	case up:
	{
		setDirection(up);
		dest_Y++;
		break;
	}
	case 4:
	case down:
	{
		setDirection(down);
		dest_Y--;
		break;
	}
	}

	if (!(world()->isAgentMovementBlockedAt(dest_X, dest_Y, this)))
	{
		moveTo(dest_X, dest_Y);
		setMovementPlan(movementPlan() - 1);
	}
	else
		setMovementPlan(0);
}
void SmartZombie::dieByFallOrBurnIfAppropriate()
{
	setDead();
	world()->playSound(SOUND_ZOMBIE_DIE);
	world()->increaseScore(2000);
}