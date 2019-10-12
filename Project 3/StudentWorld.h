#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>
using namespace std;

class Actor;
class Penelope;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual ~StudentWorld();

	virtual int init();
	virtual int move();
	virtual void cleanUp();

	Penelope* getPen();

	// Add an actor to the world.
	void addActor(Actor* a);

	// Increase citizen count
	void addCitizen();

	// Record that one more citizen on the current level is gone (exited,
	// died, or turned into a zombie).
	void recordCitizenGone();

	// Return number of citizens
	int numCitizens();

	// Indicate that the player has finished the level if all citizens
	// are gone.
	void recordLevelFinishedIfAllCitizensGone();

	bool levelFinished();

	void resetLevelFinished();

	// For each actor overlapping a, activate a if appropriate.
	void activateOnAppropriateActors(Actor* a);

	// Is an agent blocked from moving to the indicated location?
	bool isAgentMovementBlockedAt(double x, double y, Actor* a) const;

	// Is creation of a flame blocked at the indicated location?
	bool isFlameBlockedAt(double x, double y) const;

	// Is there something at the indicated location that might cause a
	// zombie to vomit?
	bool isZombieVomitTargetAt(double x, double y) const;

	// Return true if there is a living human, otherwise false.  If true,
	 // otherX, otherY, and distance will be set to the location and distance
	 // of the human nearest to (x,y).
	bool locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance);

	// Return true if there is a living zombie or Penelope, otherwise false.
	// If true, otherX, otherY, and distance will be set to the location and
	// distance of the one nearest to (x,y), and isThreat will be set to true
	// if it's a zombie, false if a Penelope.
	bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const;

	// Return true if there is a living zombie, false otherwise.  If true,
	// otherX, otherY and distance will be set to the location and distance
	// of the one nearest to (x,y).
	bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const;

	string getGameStatText();

	// ********* One or two more functions will appear here shortly relating
	// ********* to finding the nearest relevant agent for citizen/smart zombie movement

private:
	list<Actor*> actors;
	Penelope* penelope;
	int citizens;
	bool levelDone;
};

#endif // STUDENTWORLD_H_
