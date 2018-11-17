#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"


class Game; 

enum WallType { topW, rightW, leftW};
const double WINDOW_ORIGIN = 0.0;

class Wall {
// --------------------- variables------------------------------------------------------
private:
	int width, height, mapWidth;
	Vector2D position;
	Vector2D collisionVector { 0.0, 0.0 };

	Texture* wallTexture = nullptr;
	Game* game = nullptr;

// ---------------------- methods ------------------------------------------------------
public:
	Wall (Game* gamePtr, Texture* texturePtr);
	~Wall ();

	// sets the correct proportions so the rendered wall can fit the screen
	void setScale (int newHeight, int newWidth, WallType type);
	// sets the wall's position and collision vector depending on the type (top, left or right)
	void setVectors (WallType type);

	// renders the wall
	void render () const;
	// checks if the ball collides with the wall and if so, returns the collision vector 
	bool collides (SDL_Rect ballRect, Vector2D &collVector);
};

