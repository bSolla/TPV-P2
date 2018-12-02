#ifndef REWARD_H
#define REWARD_H

#include "MovingObject.h"

// ----------- Function object hierarchy to manage the effects of each reward ------------------------
// Base abstract class Action
class Action {
public:
	Action () {}
	virtual void operator()(Game *gamePtr) = 0; // this is a placeholder for the specific action each reward has
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


// TODO: FINISH THESE TWO ACTIONS
// Make the paddle longer
class EnlargePaddle : public Action {
public:
	EnlargePaddle() {}
	virtual void operator()(Game* gamePtr) { std::cout << "paddle enlarged\n"; }
};


// Make the paddle shorter
class ShrinkPaddle : public Action {
public:
	ShrinkPaddle() {}
	virtual void operator()(Game *gamePtr) { std::cout << "paddle shrunk\n"; }
};




// ----------------------------------  R E W A R D S  -----------------------------------------------
class Reward : public MovingObject {
private:

public:
	Reward ();
	~Reward ();
};

#endif 