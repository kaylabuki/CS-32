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
					{
						Actor* wall = new Wall(this, col, row);
						wall->setAlive(true);
						actors.push_back(wall);
						break;
					}
					case Level::player:
					{
						Actor* penelope = new Penelope(this, col, row);
						penelope->setAlive(true);
						actors.push_back(penelope);
						break;
					}
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
		if((*it)->alive())
		{
			// Tell current actor to doSomething()
			(*it)->doSomething();
			// Iterate through list to find Penelope. If found dead, return GWSTATUS_PLAYER_DEAD
			list<Actor*>::iterator findPenelope = actors.begin();
			while (findPenelope != actors.end())
			{
				if((*it)->isPenelope() && !((*it)->alive()))
					return GWSTATUS_PLAYER_DIED;
			}
			//check if Penelope completed the current level
			//CREATE FUNCTION TO CHECK IF LEVEL HAS BEEN COMPLETED
				return GWSTATUS_FINISHED_LEVEL;
		}
	}

	it = actors.begin();
	while (it != actors.end())
	{
		if(!(*it)->alive())
		{
			delete *it;
			it = actors.erase(it);
		}
		else
			it++;
	}

	//	UPDATE DISPLAY TEXT 
	//	UPDATE THE SCORE/LIVES/LEVEL AT THE TOP OF THE SCREEN
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

bool getSWKey(StudentWorld* sw, int& ch)
{
	return sw->getKey(ch);
}

string StudentWorld::getContents(double col, double row)
{
	//creates Level object using assetPath() 
	Level lev(assetPath());
	//creates stringstream text file name using getLevel()
	ostringstream levelFile;
	levelFile.fill('0');
	levelFile << "level" << setw(2) << getLevel() << ".txt";
	//iterates through level file to find locations of Penelope and the walls
	lev.loadLevel(levelFile.str());
	Level::MazeEntry ge = lev.getContentsOf(col, row);
	switch (ge)
	{
		case Level::empty:
		{
			return;
			break;
		}
		case Level::wall:
		{
			return "wall";
			break;
		}
		case Level::player:
		{
			return "player";
		}
	}
}