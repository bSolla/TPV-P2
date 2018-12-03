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
Reward::Reward (Game *gamePtr, RewardType rewardType) {
	game = gamePtr;
	setActionType (rewardType);
}


Reward::~Reward () {
	delete action;
}


void Reward::setActionType (RewardType rewardType) {
	switch (rewardType) {
	case L: 
		action = new LevelUp ();
		break;
	case R:
		action = new RewardLife ();
		break;
	case E:
		// fill
		break;
	case S:
		// fill
		break;
	default:
		break;
	}
}


void Reward::update () {
	int paddleY = game->getMapHeight () - STANDARD_CELL_HEIGHT * 3; // one cell used by the info bar, other one as a spacer, and the paddle cell height

	MovingObject::update ();

	if (position.getY () > paddleY) {
		if (game->rewardCollides (SDL_Rect { int(position.getX ()), int(position.getY ()), STANDARD_CELL_HEIGHT, STANDARD_CELL_WIDTH })) {
			rewardAction (game, action);
			game->killObject (itList);
		}
		else if (position.getY () > paddleY + STANDARD_CELL_HEIGHT) {
			game->killObject (itList);
		}
	}
}


void Reward::loadFromFile (ifstream & file) {
}


void Reward::saveToFile (ofstream & file) {
}
