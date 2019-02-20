#include "StudentWorld.h"
#include "GameConstants.h"
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
	//iterates through level file to find locations of Penelope and the walls
	Level::LoadResult result = lev.loadLevel(levelFile.str());
	if (result == Level::load_success)
	{
		for (int col = 0; col < 16; col++)
		{
			for (int row = 0; row < 16; row++)
			{
				Level::MazeEntry ge = lev.getContentsOf(col, row);
				switch (ge)
				{
				case Level::wall:
					Actor* wall = new Wall(this, col, row);
					//add to list
					break;
				case Level::player:
					Actor* penelope = new Penelope(this, col, row);
					//add to list
					break;
				}
			}
		}
		return GWSTATUS_CONTINUE_GAME;
	}
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

bool getSWKey(StudentWorld* sw, int& ch)
{
	return sw->getKey(ch);
}