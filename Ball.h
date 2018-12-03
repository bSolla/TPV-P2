#pragma once
#include "checkML.h"
#include "Texture.h"
#include "Vector2D.h"
#include "MovingObject.h"

const double MAX_SPEED_MODULE = 6;
const double BASE_SPEED = -2;

class Game;

class Ball : public MovingObject{
// --------------------- variables------------------------------------------------------
private:
	int cellSize = STANDARD_CELL_HEIGHT;


// ---------------------- methods ------------------------------------------------------
public:
	Ball (Game* gamePtr);
	~Ball ();

	// initializes the ball position in the center of the map, just over the paddle
	void setInitialPosition (int mapWidth, int verticalOffset);
	// renders the ball
	virtual void render ();
	// checks and handles the collisions
	void checkCollisions ();
	// checks if the ball has fallen down the screen
	bool checkBallOut ();
	// updates the ball position
	virtual void update ();

	virtual void handleEvents (SDL_Event &e) {}

	virtual void loadFromFile (ifstream &file);
	virtual void saveToFile (ofstream &file);
};

