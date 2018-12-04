#pragma once
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "Utilities.h"

enum TextureTypes {numbers, level, lives};
const string TEXTURE_NAME_NUMBERS = "images\\numbers.png";
const string TEXTURE_NAME_LEVEL = "images\\level.png";
const string TEXTURE_NAME_LIVES = "images\\lives.png";

const uint N_DIVISIONS = 20;

class Game;

class InfoBar {
// --------------------- variables------------------------------------------------------
private:
	Vector2D position;
	uint cellHeight = STANDARD_CELL_HEIGHT;
	uint mapWidth;
	Texture* textures[3];

	Game* game;

// ---------------------- methods ------------------------------------------------------
public:
	InfoBar (Game *gamePtr);
	~InfoBar ();

	// creates and loads the needed textures
	void loadTextures ();
	// renders the time and level
	void render (uint seconds, uint minutes, uint level, uint lives);
};

