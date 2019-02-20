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

int StudentWorld::move() //COMMENTED TO-DO LIST!!!!
{
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		// create alive function and test to see if the actor it points to is alive
		{
			(*it)->doSomething();
			//check if Penelope died during this tick
				return GWSTATUS_PLAYER_DIED;
			//check if Penelope completed the current level
				return GWSTATUS_FINISHED_LEVEL;
		}
	}

	it = actors.begin();
	while (it != actors.end())
	{
		if(true)// create alive function and test to see if the actor it points to is alive
		{
			delete *it;
			it = actors.erase(it);
		}
		else
			it++;
	}

	//	Update Display Text // update the score/lives/level text at screen top
	// the player hasn’t completed the current level and hasn’t died, so
	// continue playing the current level
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

bool getSWKey(StudentWorld* sw, int& ch)
{
	return sw->getKey(ch);
}