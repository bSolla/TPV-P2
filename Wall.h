#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ArkanoidObject.h"

using namespace std;

class Game; 

enum WallType { topW, rightW, leftW};
const double WINDOW_ORIGIN = 0.0;

class Wall : public ArkanoidObject{
// --------------------- variables------------------------------------------------------
private:
	Vector2D collisionVector { 0.0, 0.0 };

// ---------------------- methods ------------------------------------------------------
public:
	Wall (Game* gamePtr, Texture* texturePtr);
	~Wall ();

	// sets the correct proportions so the rendered wall can fit the screen
	void setScale (int newHeight, int newWidth, WallType type);
	// sets the wall's position and collision vector depending on the type (top, left or right)
	void setVectors (WallType type);

	// renders the wall
	virtual void render ();
	// checks if the ball collides with the wall and if so, returns the collision vector 
	virtual bool collides (SDL_Rect ballRect, Vector2D &collVector);

	virtual void loadFromFile (ifstream &file);
	virtual void saveToFile (ofstream &file);
	virtual void update () {}
	virtual void handleEvents(SDL_Event &e) {}
};

