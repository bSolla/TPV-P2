#include "Wall.h"
#include "Game.h"


Wall::Wall (Game* gamePtr, Texture* texturePtr) {
	game = gamePtr;
	wallTexture = texturePtr;
	SDL_QueryTexture (wallTexture->getTexture(), NULL, NULL, &width, &height);
}


Wall::~Wall () {
	game = nullptr;
	wallTexture = nullptr;
}


void Wall::render () const {
	SDL_Rect destRect { position.getX (), position.getY (), width, height };

	wallTexture->render (destRect);
}


void Wall::setScale (int newHeight, int newWidth, WallType type) { 
	width = newWidth;
	height = newHeight;

	setVectors (type);
}


void Wall::setVectors (WallType type) {
	switch (type) {
	case topW:
		position.setX (WINDOW_ORIGIN);
		position.setY (WINDOW_ORIGIN);
		collisionVector.setX (0.0);
		collisionVector.setY (1.0);
		break;
	case rightW:
		position.setX (game->getMapWidth() - width);
		position.setY (WINDOW_ORIGIN);
		collisionVector.setX (-1.0);
		collisionVector.setY (0.0);
		break;
	case leftW:
		position.setX (WINDOW_ORIGIN);
		position.setY (WINDOW_ORIGIN);
		collisionVector.setX (1.0);
		collisionVector.setY (0.0);
		break;
	default:
		break;
	}
}


bool Wall::collides (SDL_Rect ballRect, Vector2D &collVector) {
	bool doesItCollide = false;

	if (collisionVector.getX() == -1.0) { // right wall
		if (ballRect.x + ballRect.w >= position.getX ()) { // the right side of the collision box is over the wall
			doesItCollide = true;
			collVector = collisionVector;
		}
	}
	else { // top or left wall
		if (ballRect.x <= (position.getX () + width) && ballRect.y <= (position.getY () + height)) { // the left and top sides of the collision box are over the wall
			doesItCollide = true;
			collVector = collisionVector;
		}
	}

	return doesItCollide;
}

