#include "ArkanoidObject.h"
#include "Texture.h"
#include "Game.h"

ArkanoidObject::ArkanoidObject(Game* gameptr, int posX, int posY, int objectWidth, int objectHeight, Texture* objectTexture, TextureNames textureName) {
	game = gameptr;
	position.setX(posX);
	position.setY(posY);
	width = objectWidth;
	height = objectHeight;
	texture = game->getTexture(textureName);
}

void ArkanoidObject::saveFromFile() {};

void ArkanoidObject::loadFromFile() {};

void ArkanoidObject::getRect() {};
