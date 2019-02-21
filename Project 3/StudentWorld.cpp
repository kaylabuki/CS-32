#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream> // REMOVE LATER!
#include <cstdlib> // CHECK IF OKAY
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
					{
						break;
					}
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
				}
			}
			cout << endl;
		}
		return GWSTATUS_CONTINUE_GAME;
	}
	return GWSTATUS_LEVEL_ERROR;
}

int StudentWorld::move() //COMMENTED TO-DO LIST!!!!
{
	list<Actor*>::iterator it = actors.begin();
	penelope->doSomething();
	while (it != actors.end())
	{
		if ((*it)->alive())
		{
			// Tell current actor to doSomething()
			(*it)->doSomething();
			// Check if penelope is dead
			if (!(penelope->alive()))
				return GWSTATUS_PLAYER_DIED;
		}
		//check if Penelope completed the current level
		//CREATE FUNCTION TO CHECK IF LEVEL HAS BEEN COMPLETED
		//return GWSTATUS_FINISHED_LEVEL;
		it++;
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

bool StudentWorld::blocked(double row, double col)
{
	cout << "Penelope's Desired Location: (" << row << ", " << col << ")" << endl;
	list<Actor*>::iterator it = actors.begin();
	while (it != actors.end())
	{
		if ((*it)->canBlockOthers())
		{
			if (abs((*it)->getY() - row) < SPRITE_HEIGHT && abs((*it)->getX() - col) < SPRITE_WIDTH)
			{
				cout << "Current actor's location: (" << (*it)->getY() << ", " << (*it)->getX() << ")" << endl;
				return true;
			}
		}
		it++;
	}
	return false;
}

//string StudentWorld::getContents(double col, double row)
//{
//	//creates Level object using assetPath() 
//	Level lev(assetPath());
//	//creates stringstream text file name using getLevel()
//	ostringstream levelFile;
//	levelFile.fill('0');
//	levelFile << "level" << setw(2) << getLevel() << ".txt";
//	//iterates through level file to find locations of Penelope and the walls
//	lev.loadLevel(levelFile.str());
//	Level::MazeEntry ge = lev.getContentsOf(col, row);
//	switch (ge)
//	{
//		case Level::empty:
//		{
//			return "";
//			break;
//		}
//		case Level::wall:
//		{
//			return "wall";
//			break;
//		}
//		case Level::player:
//		{
//			return "player";
//			break;
//		}
//	}
//}