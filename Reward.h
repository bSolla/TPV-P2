#ifndef REWARD_H
#define REWARD_H

#include "MovingObject.h"
#include <list>

// ----------- Function object hierarchy to manage the effects of each reward ------------------------
// Base class Action
class Action {
public:
	Action () {}
	virtual void operator()(Game *gamePtr) {} // this is a placeholder for the specific action each reward has
};

// Change to the next level
class LevelUp: public Action {
public:
	LevelUp() {}
	virtual void operator()(Game* gamePtr);
};

// Get one extra life
class RewardLife : public Action {
public:
	RewardLife () {}
	virtual void operator()(Game* gamePtr);
};


// Make the paddle longer
class EnlargePaddle : public Action {
public:
	EnlargePaddle() {}
	virtual void operator()(Game* gamePtr);
};


// Make the paddle shorter
class ShrinkPaddle : public Action {
public:
	ShrinkPaddle() {}
	virtual void operator()(Game *gamePtr);
};


enum RewardType {L, R, E, S};

// ----------------------------------  R E W A R D S  -----------------------------------------------
class Reward : public MovingObject {
// --------------------- variables------------------------------------------------------
private:
	Action *action = nullptr;
	Game *game = nullptr;

	list<ArkanoidObject*>::iterator itList;

	double verticalSpeed = 4;
	int spriteSheetCol = 0;
	int spriteSheetRow = 0;
	RewardType type;

// ---------------------- methods ------------------------------------------------------
private:
	void setActionType (RewardType rewardType);
	void setSprites (RewardType rewardType);

public:
	Reward (Game *gamePtr, RewardType rewardType);
	Reward (Game *gamePtr);
	~Reward ();

	// used to set the iterator to the position of the list the reward is in 
	void setItList (list<ArkanoidObject*>::iterator it) { itList = it; }
	void setPosition (const SDL_Rect &rect) { position.setX (rect.x); position.setY (rect.y); }

	virtual void update ();

	virtual void render ();

	virtual void handleEvents (SDL_Event &e) {}

	virtual void loadFromFile (ifstream &file);
	virtual void saveToFile (ofstream &file);
};

#endif 