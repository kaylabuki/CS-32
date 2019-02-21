#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream> // REMOVE LATER!
#include <cstdlib> // CHECK IF OKAY
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath)
{
	
}

StudentWorld::~StudentWorld()
{
	this->cleanUp();
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
					case Level::wall:
					{
						Actor* wall = new Wall(this, col, row);
						wall->setAlive(true);
						actors.push_back(wall);
						break;
					}
					case Level::player:
					{
						Actor* pnlp = new Penelope(this, col, row);
						penelope = pnlp;
						break;
					}
					default:
						break;
				}
			}
		}
		cout << endl;
		return GWSTATUS_CONTINUE_GAME;
	}
	return GWSTATUS_LEVEL_ERROR;
}

int StudentWorld::move()
{
	// Tell Penelope to doSomething()
	penelope->doSomething();
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		// Tell current actor to doSomething()
		(*it)->doSomething();
		// Increment iterator
		it++;
	}
	it = actors.begin();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		delete *it;
		actors.pop_back();
		it++;
	}
	delete penelope;
}

bool StudentWorld::blocked(double col, double row)
{
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->canBlockOthers())
		{
			if (abs((*it)->getY() - row) < SPRITE_HEIGHT && abs((*it)->getX() - col) < SPRITE_WIDTH)
			{
				return true;
			}
		}
		it++;
	}
	return false;
}
