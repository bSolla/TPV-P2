#pragma once
#include "checkML.h"
#include "Texture.h"
#include "Vector2D.h"


const double MAX_SPEED_MODULE = 6;
const double BASE_SPEED = -2;

class Game;

class Ball {
// --------------------- variables------------------------------------------------------
private:
	int cellSize = 20;
	Vector2D position, speed { BASE_SPEED, BASE_SPEED*2 };

	Texture* texture = nullptr;
	Game* game = nullptr;

// ---------------------- methods ------------------------------------------------------
public:
	Ball (Game* gamePtr);
	~Ball ();

	// initializes the ball position in the center of the map, just over the paddle
	void setInitialPosition (int mapWidth, int verticalOffset);
	// renders the ball
	void render () const;
	// checks and handles the collisions
	void checkCollisions ();
	// checks if the ball has fallen down the screen
	bool checkBallOut ();
	// updates the ball position
	void update ();
};

