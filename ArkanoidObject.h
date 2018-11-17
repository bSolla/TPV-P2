#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Game;

class ArkanoidObject : public GameObject {
private:
	Vector2D position;
	int width, height;
	Texture* texture;
	Game* game = nullptr;

public:
	ArkanoidObject(Game* gameptr, int posX, int posY, int width, int height, Texture* texture, TextureNames textureName);

	virtual void loadFromFile() = 0;

	virtual void saveFromFile() = 0;

	virtual void getRect() = 0;

};