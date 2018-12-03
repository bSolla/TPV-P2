#pragma once
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Utilities.h"

class Game;

class ArkanoidObject : public GameObject {
protected:
	Vector2D position;
	int width = STANDARD_CELL_WIDTH, height = STANDARD_CELL_HEIGHT;

	Texture* texture = nullptr;
	Game* game = nullptr;

public:
	ArkanoidObject () {};
	ArkanoidObject(Game* gameptr, int posX, int posY, int width, int height, Texture* texture, TextureNames textureName);

	virtual ~ArkanoidObject () {};

	virtual void loadFromFile(ifstream &file);

	virtual void saveToFile(ofstream &file);

	virtual SDL_Rect getRect();

	virtual bool collides (const SDL_Rect& rect, Vector2D& collVector) { return false; };

	virtual void render ();

	virtual void update() = 0;
};