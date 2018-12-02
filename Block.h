#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Utilities.h"
#include "ArkanoidObject.h"

class Game;

enum BlockColor { blue, green, red, yellow, black, purple};


class Block : public ArkanoidObject{
// --------------------- variables------------------------------------------------------
private:
	int row, col; // position in the sprite sheet
	BlockColor color;

// ---------------------- methods ------------------------------------------------------
public:
	Block () {};
	Block (Game *gamePtr, int colorIndex);
	~Block ();
	
	// sets the internal color atribute to newColor, and calculates the sprite sheet row and column to be used when rendering 
	void setColor (BlockColor newColor);
	// renders the block
	void render ();

	// get functions for the position (both X and Y)
	int getX () const { return position.getX (); }
	int getY () const { return position.getY (); }

	// initializes the block position according to the matrix row and column index (the [c][r]) 
	void setPosition (uint matrixColumnIndex, uint matrixRowIndex);

	int getColor() { return color + 1; }

	virtual void loadFromFile (ifstream &file) {} // it is done directly in blocksmap, because the block needs the color for the constructor, and to find the right texture
	virtual void saveToFile (ofstream &file);
	virtual void update () {}
	virtual void handleEvents(SDL_Event &e) {}
};

