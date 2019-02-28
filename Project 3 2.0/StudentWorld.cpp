#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <cstdlib>
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
	levelFile << "level" << setw(2) << getLevel() + 1 << ".txt";
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
}

int StudentWorld::move()
{
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
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		delete *it;
		it++;
	}
	actors.clear();
	delete penelope;
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
			it++;
		}
	}
	return false;
}

bool StudentWorld::isZombieVomitTargetAt(double x, double y) const
{
	list<Actor*>::const_iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->getX() == x && (*it)->getY() == y)
		{
			if ((*it)->triggersZombieVomit())
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
	scoreNum << setw(6) << getScore();
	statText << "Score: " << scoreNum.str() << "  ";
	statText << "Level: " << getLevel() << "  ";
	statText << "Lives: " << getLives() << "  ";
	statText << "Vaccines: " << penelope->getNumVaccines() << "  ";
	statText << "Flame: " << penelope->getNumFlameCharges() << "  ";
	statText << "Mines: " << penelope->getNumLandmines() << "  ";
	statText << "Infected: " << penelope->infectionTime();
	return statText.str();
}