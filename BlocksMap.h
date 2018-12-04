#pragma once
#include "Block.h"
#include "checkML.h"
#include "ArkanoidObject.h"
#include "FileNotFoundError.h"

const string LEVELS_PATH = "levels\\";

class Game;

class BlocksMap : public ArkanoidObject{
// --------------------- variables------------------------------------------------------
private:
	uint rows, cols;
	uint cellHeight = 20, cellWidth = 60;
	uint mapHeight, mapWidth;
	uint nBlocks = 0;

	Block*** cells = nullptr;
	Game* game = nullptr;

// ---------------------- methods ------------------------------------------------------
public:
	BlocksMap (Game* gamePtr);
	~BlocksMap ();

	// deletes and sets the specified block to nullPtr
	void setBlockNull (Block* blockPtr);

	// loads data from the .ark files and saves it to a Block matrix (cells); also scales the window size according to the number of rows and cols
	void load (const string &filename);
	Block* collides (const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	Block* blockAt (const Vector2D& p);
	// renders the whole Block matrix
	virtual void render ();
	
	// checks if the level is clear, and if so calls game->setLevelClear
	virtual void update ();
	virtual void saveToFile(ofstream &file);
	virtual void loadFromFile(ifstream &file);
	virtual void handleEvents(SDL_Event &e) {}


private:
	// given a point, calculates the row and column it occupies in the matrix
	void getBlockMatrixCoordinates (const Vector2D &point, int &c, int &r);
};

