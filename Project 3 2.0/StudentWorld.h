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

	// Add an actor to the world.
	void addActor(Actor* a);

	// Record that one more citizen on the current level is gone (exited,
	// died, or turned into a zombie).
	void recordCitizenGone();

	// Indicate that the player has finished the level if all citizens
	// are gone.
	void recordLevelFinishedIfAllCitizensGone();

	// For each actor overlapping a, activate a if appropriate.
	void activateOnAppropriateActors(Actor* a);

	// Is an agent blocked from moving to the indicated location?
	bool isAgentMovementBlockedAt(double x, double y) const;

	// Is creation of a flame blocked at the indicated location?
	bool isFlameBlockedAt(double x, double y) const;

	// Is there something at the indicated location that might cause a
	// zombie to vomit?
	bool isZombieVomitTargetAt(double x, double y) const;

	// ********* One or two more functions will appear here shortly relating
	// ********* to finding the nearest relevant agent for citizen/smart zombie movement

private:
	list<Actor*> actors;
	Actor* penelope;
};

#endif // STUDENTWORLD_H_
