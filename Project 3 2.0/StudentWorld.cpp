#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
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

int StudentWorld::init()
{
	//creates Level object using assetPath() 
	Level lev(assetPath());
	//creates stringstream text file name using getLevel()
	ostringstream levelFile;
	levelFile.fill('0');
	levelFile << "level" << setw(2) << getLevel() << ".txt";
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
				case Level::exit:
				case Level::wall:
				case Level::player:
				}
			}
		}
		cout << endl;
		return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}

void StudentWorld::addActor(Actor* a)
{}

void StudentWorld::recordCitizenGone()
{}

void StudentWorld::recordLevelFinishedIfAllCitizensGone()
{}

void StudentWorld::activateOnAppropriateActors(Actor* a)
{}

bool StudentWorld::isAgentMovementBlockedAt(double x, double y) const
{}

bool StudentWorld::isFlameBlockedAt(double x, double y) const
{}

bool StudentWorld::isZombieVomitTargetAt(double x, double y) const
{}