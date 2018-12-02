#pragma once
#include <math.h>
#include "checkML.h"
#include "Texture.h"
#include "Vector2D.h"
#include "MovingObject.h"

const uint MAX_ANGLE = 45;
const double RADIAN_CONVERSION_FACTOR = M_PI / 180;

class Game;

class Paddle : public MovingObject{
// --------------------- variables------------------------------------------------------
private:
	uint mapWidth = 0;
	double basicIncrement = 10;

// ---------------------- methods ------------------------------------------------------
public:
	Paddle (Game* gamePtr);
	~Paddle ();

	// renders the paddle
	virtual void render();
	// initializes the paddle position to the middle of the map and a vertical offset
	void setInitialPosition (int mapWidth, int verticalOffset);
	// given a SDL_Event e, checks for left/right arrows and changes the paddle's speed;
	virtual void handleEvents (SDL_Event &e);
	// checks if the ball collides with the paddle and if so, returns the collision vector (with a degree proportional to the paddle collision point)
	bool collides (SDL_Rect ballRect, Vector2D &collVector);
	// updates the paddle position
	virtual void update ();

	virtual void saveToFile(ofstream &file);
	virtual void loadFromFile(ifstream &file);
};

