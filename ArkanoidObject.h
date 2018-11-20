#pragma once
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

	virtual void loadFromFile() = 0;

	virtual void saveToFile() = 0;

	virtual SDL_Rect getRect();

	virtual void render ();
};