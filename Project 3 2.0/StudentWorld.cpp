#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
	citizens = 0;
	levelDone = false;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

int StudentWorld::init()
{
	resetLevelFinished();
	//creates Level object using assetPath() 
	Level lev(assetPath());
	//creates stringstream text file name using getLevel()
	ostringstream levelFile;
	levelFile.fill('0');
	levelFile << "level" << setw(2) << getLevel() << ".txt"; //CHANGE LATER
	//Iterates through level file to find locations of Penelope and the walls
	Level::LoadResult result = lev.loadLevel(levelFile.str());
	Level::MazeEntry ge;
	if (result == Level::load_success)
	{
		for (int row = 0; row < 16; row++)
		{
			for (int col = 0; col < 16; col++)
			{
				ge = lev.getContentsOf(col, row);
				switch (ge)
				{
					case Level::empty:
					{
						break;
					}
					case Level::wall:
					{
						Actor* wall = new Wall(this, col, row);
						addActor(wall);
						break;
					}
					case Level::exit:
					{
						Actor* exit = new Exit(this, col, row);
						addActor(exit);
						break;
					}
					case Level::player:
					{
						penelope = new Penelope(this, col, row);
						break;
					}
					case Level::citizen:
					{
						Actor* citizen = new Citizen(this, col, row);
						addActor(citizen);
						addCitizen();
						break;
					}
					case Level::pit:
					{
						Actor* pit = new Pit(this, col, row);
						addActor(pit);
						break;
					}
					case Level::dumb_zombie:
					{
						Actor* dumbZombie = new DumbZombie(this, col, row);
						addActor(dumbZombie);
						break;
					}
					case Level::smart_zombie:
					{
						Actor* smartZombie = new SmartZombie(this, col, row);
						addActor(smartZombie);
						break;
					}
					case Level::gas_can_goodie:
					{
						Actor* gasCanGoodie = new GasCanGoodie(this, col, row);
						addActor(gasCanGoodie);
						break;
					}
					case Level::landmine_goodie:
					{
						Actor* landmineGoodie = new LandmineGoodie(this, col, row);
						addActor(landmineGoodie);
						break;
					}
					case Level::vaccine_goodie:
					{
						Actor* vaccineGoodie = new VaccineGoodie(this, col, row);
						addActor(vaccineGoodie);
						break;
					}
				}
			}
		}
		cout << endl;
		return GWSTATUS_CONTINUE_GAME;
	}
	else if (result == Level::load_fail_bad_format)
	{
		return GWSTATUS_LEVEL_ERROR;
	}
	else
	{
		return GWSTATUS_PLAYER_WON;
	}
}

int StudentWorld::move()
{
	if(!penelope->isDead())
		penelope->doSomething();
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		// Tell current actor to doSomething()
		if(!((*it)->isDead()))
			(*it)->doSomething();
		// Check if penelope died during this tick
		if (penelope->isDead())
			return GWSTATUS_PLAYER_DIED;
		// Check if the level is finished
		if (levelFinished())
			return GWSTATUS_FINISHED_LEVEL;
		// Increment iterator
		it++;
	}

	it = actors.begin();
	// Remove newly-dead actors after each tick
	while (it != actors.end())
	{
		if ((*it)->isDead())
		{
			delete *it;
			it = actors.erase(it);
			it--;
		}
		it++;
	}
	setGameStatText(getGameStatText());
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	delete penelope;
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		delete *it;
		it++;
	}
	actors.clear();
}

Penelope* StudentWorld::getPen()
{
	return penelope;
}

void StudentWorld::addActor(Actor* a)
{
	actors.push_back(a);
}

void StudentWorld::addCitizen()
{
	citizens++;
}

void StudentWorld::recordCitizenGone()
{
	citizens--;
}

int StudentWorld::numCitizens()
{
	return citizens;
}

void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{
	levelDone = true;
}

bool StudentWorld::levelFinished()
{
	return levelDone;
}

void StudentWorld::resetLevelFinished()
{
	levelDone = false;
}

// Return true if there is a living zombie or Penelope, otherwise false.
	// If true, otherX, otherY, and distance will be set to the location and
	// distance of the one nearest to (x,y), and isThreat will be set to true
	// if it's a zombie, false if a Penelope.
bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const
{
	double minDis = sqrt((256 * 256) + (256 * 256));
	if (!(penelope->isDead()))
	{
		double deltaX = penelope->getX() - x;
		double deltaY = penelope->getY() - y;
		double minDis = sqrt((deltaX*deltaX) + (deltaY*deltaY));
	}
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->triggersCitizens())
		{
			double newDeltaX = (*it)->getX() - x;
			double newDeltaY = (*it)->getY() - y;
			double newDis = sqrt((newDeltaX*newDeltaX) + (newDeltaY*newDeltaY));
			if (newDis < minDis)
			{
				minDis = newDis;
				otherX = (*it)->getX();
				otherY = (*it)->getY();
				distance = minDis;
				isThreat = (*it)->threatensCitizens();
			}
		}
		it++;
	}
	if (minDis == sqrt((256 * 256) + (256 * 256)))
		return false;
	else
		return true;
}

// Return true if there is a living zombie, false otherwise.  If true,
	// otherX, otherY and distance will be set to the location and distance
	// of the one nearest to (x,y).
bool StudentWorld::locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const
{
	double minDis = sqrt((256 * 256) + (256 * 256));
	double deltaX = 256;
	double deltaY = 256;

	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->threatensCitizens())
		{
			double newDeltaX = (*it)->getX() - x;
			double newDeltaY = (*it)->getY() - y;
			double newDis = sqrt((newDeltaX*newDeltaX) + (newDeltaY*newDeltaY));
			if (newDis < minDis)
			{
				minDis = newDis;
				otherX = (*it)->getX();
				otherY = (*it)->getY();
				distance = minDis;
			}
		}
		it++;
	}
	if (minDis == sqrt((256 * 256) + (256 * 256)))
		return false;
	else
		return true;
}

bool StudentWorld::locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance)
{
	double minDis = sqrt((256 * 256) + (256 * 256));
	if (!(penelope->isDead()))
	{
		double deltaX = penelope->getX() - x;
		double deltaY = penelope->getY() - y;
		double minDis = sqrt((deltaX*deltaX) + (deltaY*deltaY));
	}
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->triggersZombieVomit())
		{
			double newDeltaX = (*it)->getX() - x;
			double newDeltaY = (*it)->getY() - y;
			double newDis = sqrt((newDeltaX*newDeltaX) + (newDeltaY*newDeltaY));
			if (newDis < minDis)
			{
				minDis = newDis;
				otherX = (*it)->getX();
				otherY = (*it)->getY();
				distance = minDis;
			}
		}
		it++;
	}
	if (minDis == sqrt((256 * 256) + (256 * 256)))
		return false;
	else
		return true;
}

void StudentWorld::activateOnAppropriateActors(Actor* a)
{
	double aX = a->getX();
	double aY = a->getY();
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		double deltaX = (*it)->getX() - aX;
		double deltaY = (*it)->getY() - aY;
		if (((deltaX*deltaX) + (deltaY*deltaY)) <= 100)
			a->activateIfAppropriate(*it);
		it++;
	}

	double deltaPX = penelope->getX() - aX;
	double deltaPY = penelope->getY() - aY;
	if (((deltaPX*deltaPX) + (deltaPY*deltaPY)) <= 100)
		a->activateIfAppropriate(penelope);
}

bool StudentWorld::isAgentMovementBlockedAt(double x, double y, Actor* a) const
{
	if (abs(penelope->getX() - x) < SPRITE_WIDTH && abs(penelope->getY() - y) < SPRITE_HEIGHT && a != penelope)
		return true;
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->blocksMovement() && (*it) != a)
		{
			if (abs((*it)->getY() - y) < SPRITE_HEIGHT && abs((*it)->getX() - x) < SPRITE_WIDTH)
			{
				return true;
			}
		}
		it++;
	}
	return false;
}

bool StudentWorld::isFlameBlockedAt(double x, double y) const
{
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if((*it)->blocksFlame())
		{
			double deltaX = (*it)->getX() - x;
			double deltaY = (*it)->getY() - y;
			if (((deltaX*deltaX) + (deltaY*deltaY)) <= 100)
				return true;
		}
		it++;
	}
	return false;
}

bool StudentWorld::isZombieVomitTargetAt(double x, double y) const
{
	double deltaPX = penelope->getX() - x;
	double deltaPY = penelope->getY() - y;
	if (((deltaPX*deltaPX) + (deltaPY*deltaPY)) <= 100)
		return true;
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->triggersZombieVomit())
		{
			double deltaX = (*it)->getX() - x;
			double deltaY = (*it)->getY() - y;
			if (((deltaX*deltaX) + (deltaY*deltaY)) <= 100)
				return true;
		}
		it++;
	}
	return false;
}

string StudentWorld::getGameStatText()
{
	ostringstream statText;
	ostringstream scoreNum;
	scoreNum.fill('0');
	if (getScore() >= 0)
		scoreNum << setw(6) << getScore();
	else
		scoreNum << "-" << setw(5) << (getScore() * -1);
	statText << "Score: " << scoreNum.str() << "  ";
	statText << "Level: " << getLevel() << "  ";
	statText << "Lives: " << getLives() << "  ";
	statText << "Vaccines: " << penelope->getNumVaccines() << "  ";
	statText << "Flame: " << penelope->getNumFlameCharges() << "  ";
	statText << "Mines: " << penelope->getNumLandmines() << "  ";
	statText << "Infected: " << penelope->infectionTime();
	return statText.str();
}