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


// TODO: CHECK FOR TYPE ERRORS AND STUFF, USING FILEFORMAT ERROR 
void ArkanoidObject::saveToFile(ofstream &file) {
	file << "\n" << position.getX() << " " << position.getY() << " ";
}

void ArkanoidObject::loadFromFile(ifstream &file) {
	double x, y;
	
	file >> x >> y;
	position.setX (x);
	position.setY (y);
}