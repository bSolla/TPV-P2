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
	// changes the size of the paddle based on a scale
	void changeSize (double scale);
	// given a SDL_Event e, checks for left/right arrows and changes the paddle's speed;
	virtual void handleEvents (SDL_Event &e);
	// checks if an object collides with the paddle and if so, returns the collision vector (with a degree proportional to the paddle collision point)
	virtual bool collides (SDL_Rect objectRect, Vector2D &collVector);
	// updates the paddle position
	virtual void update ();

	virtual void saveToFile(ofstream &file);
	virtual void loadFromFile(ifstream &file);
};

