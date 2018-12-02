#include "Reward.h"
#include "Game.h"

// ----------- Function object hierarchy to manage the effects of each reward ------------------------
void LevelUp::operator()(Game *gamePtr) {
	gamePtr->setLevelClear ();
}

void RewardLife::operator()(Game *gamePtr) {
	gamePtr->increaseLives ();
}

void rewardAction (Game *gamePtr, Action *action) {
	return (*action)(gamePtr);
}

// ----------------------------------  R E W A R D S  -----------------------------------------------
Reward::Reward () {
}


Reward::~Reward () {
}
