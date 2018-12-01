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


void ArkanoidObject::render (){
	texture->render (getRect ());
}

SDL_Rect ArkanoidObject::getRect () {
	SDL_Rect rect { position.getX (), position.getY (), width, height };

	return rect;
}

void ArkanoidObject::saveToFile(ofstream file) {
	file << position.getX() << " " << position.getY() << " " << width << " " << height;
}

void ArkanoidObject::loadFromFile(ifstream file) {}